- Line 9. Corrected code: h=0.1;
- Line 18. Corrected code: yNew[i]=(1.0-(5.0*h/2.0))*yOld[i+1];
- Line 19. Corrected code: yNew[i]=yNew[i]+(1.0+(5.0*h/2.0))*yNew[i-1]-10.0*h*h*x[i];
- Line 22. Corrected code: if(Error>Tolerance) Done=false;
- Line 28: Corrected code: for(int i=0;i<=10;i++) yOld[i]=yNew[i];
