function [ c, iter ] = rootBisection( f, a, b, tol )
%ROOTBISECTION 

    fa = f(a);
    
 
    it = 1;
    %%iter(1:40) = 0;
    while abs(b - a) > tol
        c = (a + b) / 2;
        fc = f(c);
        
        %%disp('iteracion');
        %%disp(it);
        %%disp(c);
        %%iter(it) = c;
        
        
        if a == c || a == b
            return;
        end
        
        if fc * fa > 0
            a = c;
            fa = fc;
        else
            b = c;
        end
        
        it = it + 1;
            
    end

end

