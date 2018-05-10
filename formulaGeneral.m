## Author: charl <charl@DESKTOP-5QEEJRC>
## Created: 2018-01-27

function [x] = formulaGeneral (a, b, c)

  x = [double( sqrt(1 + (2/b) * sqrt(a * c)) ), double( sqrt(1 - (2/b) * sqrt(a * c)) )];
  ##a3 = double( a1 * a2 )
  ##det = b * a3;
  ##x = [ (b - det) / (2 * a), (b + det) / (2 * a) ];
  ##x = sqrt(1 - (4*a*c)/(b^2)) / (2 * a * b);  
      
endfunction
