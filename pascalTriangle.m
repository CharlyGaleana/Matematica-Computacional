function [PT] = pascalTriangle (n)

  PT(1:n, 1:n) = 0;
  PT(1:n, 1:1) = 1;
  
  for i = 2:n
    for j = 2:i
      PT(i, j) = PT(i - 1, j) + PT(i - 1, j - 1);
    end
  end
  
endfunction
