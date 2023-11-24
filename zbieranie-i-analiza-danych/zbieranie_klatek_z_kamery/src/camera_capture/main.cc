#include <opencv2/imgcodecs.hpp>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <iostream>
#include <vector>
#include <string>

#include <opencv2/core/cvstd.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

cv::Mat global_frame;
std::mutex global_frame_mutex;
std::atomic<int> new_frames_counter(0);
std::atomic<bool> end_the_program(false);

void frame_capture(cv::VideoCapture * cap)
{
  global_frame_mutex.lock();

  cv::Mat frame;

  if (cap->isOpened()) {
    cap->read(global_frame);
    global_frame_mutex.unlock();
  }

  while (cap->isOpened() && !end_the_program) {
    cap->read(frame);
    global_frame_mutex.lock();
    global_frame = frame;
    new_frames_counter++;
    global_frame_mutex.unlock();
  }
}

int main(int argc, char ** argv, char ** envp)
{
  const cv::String vid_dev = argv[1] ? argv[1] : "/dev/video0";
  cv::VideoCapture cap = cv::VideoCapture(vid_dev);

  const cv::String winname = "Display frame";
  cv::namedWindow(winname, cv::WINDOW_AUTOSIZE);

  std::thread capture_thread(frame_capture, &cap);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "Main thread out of sleep\n";

  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  auto diff = std::chrono::duration<double>(0);

  std::vector<cv::Mat> saved_frames;

  while (!end_the_program) {
    if(new_frames_counter.load()) {
      global_frame_mutex.lock();
      cv::imshow(winname, global_frame);
      int missed_frames = new_frames_counter.load() - 1;
      new_frames_counter.store(0);
      if (saved_frames.size() < 30)
	saved_frames.push_back(global_frame);
      else
	end_the_program = true;
      global_frame_mutex.unlock();
      end = std::chrono::high_resolution_clock::now();
      diff = end - start;
      start = std::chrono::high_resolution_clock::now();
      double fps = 1/diff.count();
      std::cout << "Missed frames " << missed_frames << std::endl;
      std::cout << "FPS " << fps << std::endl;
      cv::waitKey(1);
    }
  }

  capture_thread.join();

  int i = 0;
  for(cv::Mat & frame : saved_frames) {
    std::string filename = "./img_" + std::to_string(i++) + ".png";
    cv::imwrite(filename, frame);
  }

  return 0;
}
