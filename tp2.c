clc;
clear;
format short;

% --- Saisie des données ---
A = input('Entrez la matrice des coefficients A = ');
B = input('Entrez le vecteur second membre B = ');

n = size(A, 1);     % nombre d’équations

L = zeros(n);       % matrice triangulaire inférieure
U = zeros(n);       % matrice triangulaire supérieure

% --- Calcul des matrices L et U selon la méthode de Doolittle ---
for j = 1:n
    
    % Calcul des éléments de L
    for i = j:n
        S = 0;
        for k = 1:j-1
            S = S + L(i,k) * U(k,j);
        end
        L(i,j) = A(i,j) - S;
    end

    % Calcul des éléments de U
    for i = j+1:n
        S = 0;
        for k = 1:j-1
            S = S + L(j,k) * U(k,i);
        end
        U(j,i) = (A(j,i) - S) / L(j,j);
    end

    % L’élément diagonal de U vaut toujours 1
    U(j,j) = 1;
end

disp('Matrice L = ');
disp(L);
disp('Matrice U = ');
disp(U);

% --- Résolution du système Lz = B (substitution avant) ---
z = zeros(n,1);
z(1) = B(1) / L(1,1);

for i = 2:n
    z(i) = (B(i) - L(i,1:i-1) * z(1:i-1)) / L(i,i);
end

% --- Résolution du système Ux = z (substitution arrière) ---
x = zeros(n,1);
x(n) = z(n);  % dernier élément

for i = n-1:-1:1
    x(i) = z(i) - U(i,i+1:n) * x(i+1:n);
end

disp('Solution x = ');
disp(x);
