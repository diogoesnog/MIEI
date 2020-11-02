function h = generate_homog(xi,yi,Xi,Yi)

n = lengh(xi);

D = [Xi(1),Yi(1),1, 0 ,0,0,- xi(1) * Xi(1), -xi(1) *Yi(1);
     0, 0,0,Xi(1),Yi(1),1, -yi(1)* Xi(1), -yi(1)* Yi(1)];


    for i=2:n
        D=[D;
            Xi(i),Yi(i),1, 0 ,0,0,-xi(i)* Xi(i), -xi(i)* Yi(i);
            0, 0,0,Xi(i),Yi(i),1, -yi(i)* Xi(i), -yi(i)* Yi(i)];
    end
    f=[xi(1);
        yi(1)];
    for i=2:n
        f=[f;
            xi(i);
            yi(i)];
    end
    
    h = pinv(D)*f;
    h = [h;1];
    
end
    
