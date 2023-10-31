#include <opencv2/core/cvstd.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

int main(int argc, char ** argv, char ** envp)
{
  const cv::String filename = argv[1] ? argv[1] : "/dev/video0";
  cv::VideoCapture cap = cv::VideoCapture(filename);

  const cv::String winname = "Display frame";
  cv::namedWindow(winname, cv::WINDOW_AUTOSIZE);

  cv::Mat frame;

  while (cap.isOpened()) {
    cap.read(frame);
    cv::imshow(winname, frame);
    cv::waitKey(20);
  }

  return 0;
}
