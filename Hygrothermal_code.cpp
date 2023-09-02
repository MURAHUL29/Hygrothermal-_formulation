#include<bits/stdc++.h>
using namespace std;


int main(){
int a;
cout<<" Enter angle of lamina ; "<<endl;
cin>>a;
//  mateial proerties: 

double a1 ,a2, b1,b2,T , E1,E2, V12, G66 , y1, y2, y3 ,q11, q12, q22, q16, q26, q66, m;
cout<<"Longitudinal coefficient of thermal expansion: "<<endl;
cin>>a1;

cout<<"Transverse coefficient of thermal expansion: "<<endl;
cin>>a2;

cout<<"Longitudinal coefficient of moisture expansion in m/m/kg/kg: "<<endl;
cin>>b1;

cout<<"Transverse coefficient of moisture expansion in m/m/kg/kg: "<<endl;
cin>>b2;

cout<<"Enter the temperature of composite  in degree centigrade: "<<endl;
cin>>T;
 
cout<<"Longitudinal elastic modulus in Pa: "<<endl;
cin>>E1;

cout<<" Transverse elastic modulus in Pa: "<<endl;
cin>>E2;

cout<<"Major Poisson’s ratio:  "<<endl;
cin>>V12;

cout<<" Shear modulus in Pa: "<<endl;
cin>>G66;

 cout<<" Enter Longitudinal Stress in Pa: "<<endl;
 cin>>y1;
 
 cout<<" Enter transverse stress in Pa: "<<endl;
 cin>>y2;
 
 cout<<" Enter shear stress in Pa: "<<endl;
 cin>>y3;

cout<<"Enter the weight of moisture absorption per unit weight of the lamina in kg/kg: "<<endl;
cin>>m;


// define a variable for compliance matrix
double S11, S12, S22,S66;

  S11= 1/E1;
  S12= -V12/E1;
  S22= 1/E2;
  S66= 1/G66;
  

   double c=cos(a*3.14159/180);
	double s=sin(a*3.14159/180);

// define a T-inverse matrix

 double x[3][3] = {{c*c,s*s,-2*s*c},{s*s,c*c,2*s*c},{s*c,-s*c,c*c-s*s}};

// Now define a compliance matrix for angle lamina

//double q11, q12, q22, q16, q26, q66 ;

 q11= (S11*c*c*c*c) + (((2*S12) +S66)*s*s*c*c) + (S22*s*s*s*s) ;
  q12= (S12)*((s*s*s*s) + (c*c*c*c)) +(s*s*c*c)*(S11+S22-S66);
  q22= (S11*s*s*s*s) + ((2*S12)+S66)*(s*s*c*c) +(S22*c*c*c*c);
  q16= ((2*S11)-(2*S12)-S66)*(s*c*c*c) - ((2*S22)-(2*S12)-S66)*(s*s*s*c) ;
  q26= ((2*S11)-(2*S12)-S66)*(s*s*s*c) - ((2*S22)-(2*S12)-S66)*(s*c*c*c);
  q66= ((2*S11)+(2*S22)-(4*S12) - S66)*(s*s*c*c) + (S66)*((c*c*c*c)+(s*s*s*s));
  
  
  // Now here we make a compliance matrix
  
  double comp[3][3]= {{q11,q12,q16}, {q12, q22, q26}, {q16, q26, q66}};
  
  // stress matrix for strain calculation
  double st[3][1] = {y1, y2, y3};
  
  //here we are calculating strain due to stress;
  
  double f1[3][1];
  
  // multiplication logic
  for(int i=0; i<3; i++){
  	for(int j=0; j<1; j++){
  		f1[i][j]=0;
  		
  		for(int k=0; k<3; k++){
  			
  			f1[i][j]+=comp[i][k]*st[k][j];
		  }
	  }
  }
  cout<<" Strain due stress"<<endl;
  for(int i=0; i<3; i++){
  	for( int j=0; j<1; j++){
  		cout<<f1[i][j]<<" ";
	  }
	  cout<<endl;
  }
  
  // now we calculate strain due to thermal elongation
  // matrix of thermal expansion 
  double Th[3][1]={a1,a2,0};
  
  //calculation of principle thermal coefficient
  double Pt[3][1];
  for(int i=0; i<3; i++){
  	for(int j=0; j<1; j++){
  		Pt[i][j]=0;
  		
  		for(int k=0; k<3; k++){
  			
  			Pt[i][j]+=x[i][k]*Th[k][j];
		  }
	  }
  }
  double Pt1[3][1]= {Pt[0][0]*T, Pt[1][0]*T, (Pt[2][0]/2)*T};
  
// Now strain due to thermal elongation
cout<<"Strain due to Thermal Elongation : "<<endl;
for(int i=0; i<3; i++){
  	for( int j=0; j<1; j++){
  		cout<<Pt1[i][j]<<" ";
	  }
	  cout<<endl;
  }
  
  // let's calculate strain due to moisture content 
  double Mc[3][1]= {b1, b2, 0};
  double Mc1[3][1];
  
  for(int i=0; i<3; i++){
  	for(int j=0; j<1; j++){
  		Mc1[i][j]=0;
  		
  		for(int k=0; k<3; k++){
  			
  			Mc1[i][j]+=x[i][k]*Mc[k][j];
		  }
	  }
  }
  
  double Mc2[3][1]= {Mc1[0][0]*T, Mc1[1][0]*T, (Mc1[2][0]/2)*T};
  
  cout<<"Strain due to Moisture content: "<<endl;
  
  for(int i=0; i<3; i++){
  	for( int j=0; j<1; j++){
  		cout<<Mc2[i][j]<<" ";
	  }
	  cout<<endl;
  }
  
  cout<<" Total strain in Lamina "<<endl;
  cout<<endl<<endl;
  cout<<"Strain in Longitudenal direction :- "<<Mc2[0][0]+Pt1[0][0]+f1[0][0]<<endl;
  cout<<"Strain in Transverse direction :- "<<Mc2[1][0]+Pt1[1][0]+f1[1][0]<<endl;
  cout<<"Shear strain  :- "<<Mc2[2][0]+Pt1[2][0]+f1[2][0]<<endl;
  
 
return 0;
}

