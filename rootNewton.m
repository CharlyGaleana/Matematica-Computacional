function [ c ] = rootNewton( f, fp, x1, it )

    xprev = x1;
    xcurr = xprev;
    for i = 1:it
        aux = xcurr;
        xcurr = xprev - f(xprev) / fp(xprev);
        xprev = aux;
        
        disp('iteracion')
        disp(i);
        disp(xcurr);
    end
    
    c = xcurr;

end

