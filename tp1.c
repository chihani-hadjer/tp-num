clear;
format short

a = input('Enter The Array of Coefficients a = '); % e.g : [1 2; 3 4]
b = input('Enter The Arrays of Constants b = ');  

n = size(a, 1);
A = [a, b];  % indent a and b in a single matrix

for k = 1:n  % loop on the columns
    [amax, im] = max(abs(A(k:n, k)));
    if amax == 0
        disp('matrix is singular, no possible solution');
        break;
    end
    
    im = im + k - 1;
    
    if im ~= k
        T = A(k, :);
        A(k, :) = A(im, :);
        A(im, :) = T;
    end
    
    for i = k+1:n
        A(i, k:n+1) = A(i, k:n+1) - (A(i, k)/A(k, k)) * A(k, k:n+1);
    end
end  % end of triangularization of the matrix

if A(n, n) == 0
    disp('matrix is singular, no possible solution ann=0');
end

x(n) = A(n, n+1) / A(n, n);  % start of backward substitution

for i = n-1:-1:1
    x(i) = (A(i, n+1) - sum(A(i, i+1:n).*x(i+1:n))) / A(i, i);
end

disp(x);
