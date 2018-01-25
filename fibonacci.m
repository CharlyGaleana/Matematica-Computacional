## Author: charl <charl@DESKTOP-5QEEJRC>
## Created: 2018-01-24

##function that calculates the first n numbers of the fibonacci series
function [fibo] = fibonacci (n)  

  fibo(1:n) = 1;
    
  for i = 3:n
    if i < 3
      fibo(i) = 1;
    else
      fibo(i) = fibo(i - 1) + fibo(i - 2);
    end
  end

endfunction
