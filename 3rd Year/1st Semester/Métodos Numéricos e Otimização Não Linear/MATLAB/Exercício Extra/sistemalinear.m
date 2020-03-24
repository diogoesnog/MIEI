A = [2.4 6.0 -2.7 5.0; -2.1 -2.7 5.9 -4.0; 3.0 5.0 -4.0 6.0; 0.9 1.9 4.7 1.8] % Definir a matriz A
b = [14.6;-11.4;14;-0.9] % O vetor B

x = A\b % Resolver o sistema linear
det(A) % Calcular o determinante da matriz
Ainv = inv(A) % Inversa da matriz
A*Ainv % Só para verificar (dá a identidade)1/1.5
