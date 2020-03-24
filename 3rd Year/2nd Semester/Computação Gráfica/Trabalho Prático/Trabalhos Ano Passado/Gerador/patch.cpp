//
//  patch.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 28/04/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "patch.h"

float maxLista(float *lista, int n_pontos){
    float max;
    int i;

    for(i=0; i<n_pontos; i+=3)
        if (lista[i]>max)
            max=lista[i];
    
    return max;
}

float minLista(float *lista, int n_pontos){
    float min;
    int i;

    for(i=0; i<n_pontos; i+=3)
        if (lista[i]<min)
            min=lista[i];
    
    return min;
}


float* getPoints(int *patchs, int n_patch, float *vertices, int n_vertices, int detail, float *normais, float *texB){
   
    float Ax,Ay,Az,Bx,By,Bz,Cx,Cy,Cz,Dx,Dy,Dz,Ex,Ey,Ez,Fx,Fy,Fz,Gx,Gy,Gz,Hx,Hy,Hz,Ix,Iy,Iz,Jx,Jy,Jz,Kx,Ky,Kz,Lx,Ly,Lz,Mx,My,Mz,Nx,Ny,Nz,Ox,Oy,Oz,Px,Py,Pz;
	float change = 1.0 / detail, *points=(float*)malloc(n_patch*(3*(detail+1)*(detail+1))*sizeof(float));
	float a,b,c,d, Xta,Yta,Zta, Xtc,Ytc,Ztc, Xn,Yn,Zn, modulo;
	int v=0,n=0,t=0,i,j,k,texX,texY;
    
	
                          
    for(k=0;k<n_patch;k++){
        
        //Para as texturas
        texX=texY=0;

        // Variables
        a = 0.0;
        b = 1.0 - a;
        c = 0.0;
        d = 1.0 - c;
    
        //Atribuir valores das patches
        Ax = vertices[3*patchs[(16*k)]];         Ay = vertices[3*patchs[(16*k)]+1];     Az = vertices[3*patchs[(16*k)]+2];
        Bx = vertices[3*patchs[(16*k+1)]];       By = vertices[3*patchs[(16*k+1)]+1];   Bz = vertices[3*patchs[(16*k)+1]+2];
        Cx = vertices[3*patchs[(16*k+2)]];       Cy = vertices[3*patchs[(16*k+2)]+1];   Cz = vertices[3*patchs[(16*k)+2]+2];
        Dx = vertices[3*patchs[(16*k+3)]];       Dy = vertices[3*patchs[(16*k+3)]+1];   Dz = vertices[3*patchs[(16*k)+3]+2];
        Ex = vertices[3*patchs[(16*k+4)]];       Ey = vertices[3*patchs[(16*k+4)]+1];   Ez = vertices[3*patchs[(16*k)+4]+2];
        Fx = vertices[3*patchs[(16*k+5)]];       Fy = vertices[3*patchs[(16*k+5)]+1];   Fz = vertices[3*patchs[(16*k)+5]+2];
        Gx = vertices[3*patchs[(16*k+6)]];       Gy = vertices[3*patchs[(16*k+6)]+1];   Gz = vertices[3*patchs[(16*k)+6]+2];
        Hx = vertices[3*patchs[(16*k+7)]];       Hy = vertices[3*patchs[(16*k+7)]+1];   Hz = vertices[3*patchs[(16*k)+7]+2];
        Ix = vertices[3*patchs[(16*k+8)]];       Iy = vertices[3*patchs[(16*k+8)]+1];   Iz = vertices[3*patchs[(16*k)+8]+2];
        Jx = vertices[3*patchs[(16*k+9)]];       Jy = vertices[3*patchs[(16*k+9)]+1];   Jz = vertices[3*patchs[(16*k)+9]+2];
        Kx = vertices[3*patchs[(16*k+10)]];      Ky = vertices[3*patchs[(16*k+10)]+1];  Kz = vertices[3*patchs[(16*k)+10]+2];
        Lx = vertices[3*patchs[(16*k+11)]];      Ly = vertices[3*patchs[(16*k+11)]+1];  Lz = vertices[3*patchs[(16*k)+11]+2];
        Mx = vertices[3*patchs[(16*k+12)]];      My = vertices[3*patchs[(16*k+12)]+1];  Mz = vertices[3*patchs[(16*k)+12]+2];
        Nx = vertices[3*patchs[(16*k+13)]];      Ny = vertices[3*patchs[(16*k+13)]+1];  Nz = vertices[3*patchs[(16*k)+13]+2];
        Ox = vertices[3*patchs[(16*k+14)]];      Oy = vertices[3*patchs[(16*k+14)]+1];  Oz = vertices[3*patchs[(16*k)+14]+2];
        Px = vertices[3*patchs[(16*k+15)]];      Py = vertices[3*patchs[(16*k+15)]+1];  Pz = vertices[3*patchs[(16*k)+15]+2];
    
        for(i=0; i<=detail; i++){
            for(j=0; j<=detail; j++){
                
                // First get the vertices
                points[v++] = Ax*a*a*a*c*c*c   + Bx*3*a*a*a*c*c*d
                            + Cx*3*a*a*a*c*d*d + Dx*a*a*a*d*d*d
                            + Ex*3*a*a*b*c*c*c + Fx*9*a*a*b*c*c*d
                            + Gx*9*a*a*b*c*d*d + Hx*3*a*a*b*d*d*d
                            + Ix*3*a*b*b*c*c*c + Jx*9*a*b*b*c*c*d
                            + Kx*9*a*b*b*c*d*d + Lx*3*a*b*b*d*d*d
                            + Mx*b*b*b*c*c*c   + Nx*3*b*b*b*c*c*d
                            + Ox*3*b*b*b*c*d*d + Px*b*b*b*d*d*d;
                                      
                points[v++] = Ay*a*a*a*c*c*c   + By*3*a*a*a*c*c*d
                            + Cy*3*a*a*a*c*d*d + Dy*a*a*a*d*d*d
                            + Ey*3*a*a*b*c*c*c + Fy*9*a*a*b*c*c*d
                            + Gy*9*a*a*b*c*d*d + Hy*3*a*a*b*d*d*d
                            + Iy*3*a*b*b*c*c*c + Jy*9*a*b*b*c*c*d
                            + Ky*9*a*b*b*c*d*d + Ly*3*a*b*b*d*d*d
                            + My*b*b*b*c*c*c   + Ny*3*b*b*b*c*c*d
                            + Oy*3*b*b*b*c*d*d + Py*b*b*b*d*d*d;
            
                points[v++] = Az*a*a*a*c*c*c   + Bz*3*a*a*a*c*c*d
                            + Cz*3*a*a*a*c*d*d + Dz*a*a*a*d*d*d
                            + Ez*3*a*a*b*c*c*c + Fz*9*a*a*b*c*c*d
                            + Gz*9*a*a*b*c*d*d + Hz*3*a*a*b*d*d*d
                            + Iz*3*a*b*b*c*c*c + Jz*9*a*b*b*c*c*d
                            + Kz*9*a*b*b*c*d*d + Lz*3*a*b*b*d*d*d
                            + Mz*b*b*b*c*c*c   + Nz*3*b*b*b*c*c*d
                            + Oz*3*b*b*b*c*d*d + Pz*b*b*b*d*d*d;
                

                //Agora os calculos para o Normal

                //Calculamos a tangente
                Xta = Ax*3*a*a*c*c*c        + Bx*9*a*a*c*c*d
                    + Cx*9*a*a*c*d*d        + Dx*3*a*a*d*d*d
                    + Ex*3*(2*a-3*a*a)*c*c*c   + Fx*9*(2*a-3*a*a)*c*c*d
                    + Gx*9*(2*a-3*a*a)*c*d*d   + Hx*3*(2*a-3*a*a)*d*d*d
                    + Ix*3*(1-4*a+3*a*a)*c*c*c + Jx*9*(1-4*a+3*a*a)*c*c*d
                    + Kx*9*(1-4*a+3*a*a)*c*d*d + Lx*3*(1-4*a+3*a*a)*d*d*d
                    + Mx*3*(2*a-1-a*a)*c*c*c   + Nx*9*(2*a-1-a*a)*c*c*d
                    + Ox*9*(2*a-1-a*a)*c*d*d   + Px*3*(2*a-1-a*a)*d*d*d;

                Yta = Ay*3*a*a*c*c*c        + By*9*a*a*c*c*d
                    + Cy*9*a*a*c*d*d        + Dy*3*a*a*d*d*d
                    + Ey*3*(2*a-3*a*a)*c*c*c   + Fy*9*(2*a-3*a*a)*c*c*d
                    + Gy*9*(2*a-3*a*a)*c*d*d   + Hy*3*(2*a-3*a*a)*d*d*d
                    + Iy*3*(1-4*a+3*a*a)*c*c*c + Jy*9*(1-4*a+3*a*a)*c*c*d
                    + Ky*9*(1-4*a+3*a*a)*c*d*d + Ly*3*(1-4*a+3*a*a)*d*d*d
                    + My*3*(2*a-1-a*a)*c*c*c   + Ny*9*(2*a-1-a*a)*c*c*d
                    + Oy*9*(2*a-1-a*a)*c*d*d   + Py*3*(2*a-1-a*a)*d*d*d;

                Zta = Az*3*a*a*c*c*c        + Bz*9*a*a*c*c*d
                    + Cz*9*a*a*c*d*d        + Dz*3*a*a*d*d*d
                    + Ez*3*(2*a-3*a*a)*c*c*c   + Fz*9*(2*a-3*a*a)*c*c*d
                    + Gz*9*(2*a-3*a*a)*c*d*d   + Hz*3*(2*a-3*a*a)*d*d*d
                    + Iz*3*(1-4*a+3*a*a)*c*c*c + Jz*9*(1-4*a+3*a*a)*c*c*d
                    + Kz*9*(1-4*a+3*a*a)*c*d*d + Lz*3*(1-4*a+3*a*a)*d*d*d
                    + Mz*3*(2*a-1-a*a)*c*c*c   + Nz*9*(2*a-1-a*a)*c*c*d
                    + Oz*9*(2*a-1-a*a)*c*d*d   + Pz*3*(2*a-1-a*a)*d*d*d;

                Xtc = Ax*3*a*a*a*c*c        + Bx*3*a*a*a*(2*c-3*c*c)
                    + Cx*3*a*a*a*(1-4*c+3*c*c) + Dx*3*a*a*a*(-1+2*c-c*c)
                    + Ex*9*a*a*b*c*c        + Fx*9*a*a*b*(2*c-3*c*c)
                    + Gx*9*a*a*b*(1-4*c+3*c*c) + Hx*9*a*a*b*(-1+2*c-c*c)
                    + Ix*9*a*b*b*c*c        + Jx*9*a*b*b*(2*c-3*c*c)
                    + Kx*9*a*b*b*(1-4*c+3*c*c) + Lx*9*a*b*b*(-1+2*c-c*c)
                    + Mx*3*b*b*b*c*c        + Nx*3*b*b*b*(2*c-3*c*c)
                    + Ox*3*b*b*b*(1-4*c+3*c*c) + Px*3*b*b*b*(-1+2*c-c*c);

                Ytc = Ay*3*a*a*a*c*c        + By*3*a*a*a*(2*c-3*c*c)
                    + Cy*3*a*a*a*(1-4*c+3*c*c) + Dy*3*a*a*a*(-1+2*c-c*c)
                    + Ey*9*a*a*b*c*c        + Fy*9*a*a*b*(2*c-3*c*c)
                    + Gy*9*a*a*b*(1-4*c+3*c*c) + Hy*9*a*a*b*(-1+2*c-c*c)
                    + Iy*9*a*b*b*c*c        + Jy*9*a*b*b*(2*c-3*c*c)
                    + Ky*9*a*b*b*(1-4*c+3*c*c) + Ly*9*a*b*b*(-1+2*c-c*c)
                    + My*3*b*b*b*c*c        + Ny*3*b*b*b*(2*c-3*c*c)
                    + Oy*3*b*b*b*(1-4*c+3*c*c) + Py*3*b*b*b*(-1+2*c-c*c);

                Ztc = Az*3*a*a*a*c*c        + Bz*3*a*a*a*(2*c-3*c*c)
                    + Cz*3*a*a*a*(1-4*c+3*c*c) + Dz*3*a*a*a*(-1+2*c-c*c)
                    + Ez*9*a*a*b*c*c        + Fz*9*a*a*b*(2*c-3*c*c)
                    + Gz*9*a*a*b*(1-4*c+3*c*c) + Hz*9*a*a*b*(-1+2*c-c*c)
                    + Iz*9*a*b*b*c*c        + Jz*9*a*b*b*(2*c-3*c*c)
                    + Kz*9*a*b*b*(1-4*c+3*c*c) + Lz*9*a*b*b*(-1+2*c-c*c)
                    + Mz*3*b*b*b*c*c        + Nz*3*b*b*b*(2*c-3*c*c)
                    + Oz*3*b*b*b*(1-4*c+3*c*c) + Pz*3*b*b*b*(-1+2*c-c*c);
                
                // Cross the tangent vectors, put the result to the normal vector array
                // Note: I simplified -((Xta*Ztc)-(Xtc*Zta)) to (Xtc*Zta) - (Xta*Ztc)
                Xn = (Yta*Ztc) - (Ytc*Zta);
                Yn = (Xtc*Zta) - (Xta*Ztc);
                Zn = (Xta*Ytc) - (Xtc*Yta);          

                modulo= sqrtf(powf(Xn, 2) + powf(Yn, 2)+ powf(Zn, 2));
                
                //Vector Unitário
                normais[n++]=-Xn/modulo;
                normais[n++]=-Yn/modulo;
                normais[n++]=-Zn/modulo;

                texB[t++]=texX++;
                texB[t++]=texY;


                //change the c-variable within the inner loop
                c += change;
                d  = 1.0 - c;
            }
            //Actualizar o TexX a cada nova linha
            texX=0;
            texY++;

            //change the a-variable outside the inner loop
            a += change;
            b  = 1.0 - a;
                                  
            // Reset the c-variable to make it ready for the inner loop again
            c = 0.0;
            d = 1.0 - c;
        }
    }

	return points;
}



void read_Patch(FILE *f_patch, FILE *f, int detail){
    
	int i=0,j=0,v=0,avanco,k,n_patch,n_vertices,n_indices,n_pontos,tex_pontos, *patchs=NULL;
	float *vertices=NULL,*points=NULL,*normais=NULL,*texB=NULL,x,y,z;
    
	fscanf(f_patch,"%d\n",&n_patch);
	patchs=(int*)malloc(16*n_patch*sizeof(int));
    
	while(i<n_patch){
		for(j=0;j<15;j++){
			fscanf(f_patch,"%d, ",&k);
			patchs[v++]=k;
		}
		fscanf(f_patch,"%d\n",&k);
		patchs[v++]=k;
		i++;
	}
    
	fscanf(f_patch,"%d\n",&n_vertices);
	vertices=(float*)malloc(3*n_vertices*sizeof(float));
	v=0;
	while(fscanf(f_patch," %f, %f, %f\n",&x,&y,&z)!=EOF){
		vertices[v++]=x;
		vertices[v++]=y;
		vertices[v++]=z;
	}

    //Nº de pontos das texturas
    n_pontos=n_patch*(3*(detail+1)*(detail+1));
    tex_pontos=n_pontos*2/3;

    normais=(float*)malloc(n_patch*(3*(detail+1)*(detail+1))*sizeof(float));
    texB=(float*)malloc(tex_pontos*sizeof(float));
    points=getPoints(patchs,n_patch,vertices,n_vertices,detail, normais, texB);
    

    //Descobrir os maximos e minimos para o ViewFrustumCulling
    fprintf(f, "%f %f %f %f %f %f\n",maxLista(points, n_pontos),minLista(points, n_pontos),maxLista(points+1, n_pontos),minLista(points+1, n_pontos),maxLista(points+2, n_pontos),minLista(points+2, n_pontos));

	//Imprimir Vertices
	fprintf(f, "%d\n",n_pontos);
    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",points[i],points[i+1],points[i+2]);
    
    //Imprimir Indices
    n_indices=n_patch * detail * detail *3*2;
    fprintf(f, "%d\n",n_indices);
    avanco=(detail+1)*(detail+1);
    for(i=0;i<n_patch;i++){
        for (j=0; j<detail; j++) {
            for (v=0; v<detail; v++) {

                fprintf(f, "%d %d %d\n",i*avanco + j*(detail+1) + v, i*avanco + j*(detail+1) + v+1 ,i*avanco + (j+1)*(detail+1) + v );
                fprintf(f, "%d %d %d\n", i*avanco + j*(detail+1) + v+1 , i*avanco + (j+1)*(detail+1) + v+1 ,i*avanco + (j+1)*(detail+1) + v );              
            }
        }
    }

    //Imprimir Normais
    for(i=0;i<n_pontos;i+=3)
       fprintf(f, "%f %f %f\n",normais[i],normais[i+1],normais[i+2]);

   //Imprimir texturas
   for(i=0;i<tex_pontos ;i+=2)
        fprintf(f, "%f %f\n",texB[i],texB[i+1]);
}




