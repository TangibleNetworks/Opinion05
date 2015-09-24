//Threshold Model with Greater than or equal to condition


#include <math.h>
#include<TN05.h> // Requires TN05.h, TN05.cpp, Keywords.txt in folder <Arduino>/Libraries/TN05/
TN Tn = TN(-1.0,1.0); // Create TN object with range [-1.0, 1.0]

boolean Opinion; //define opinions green and blue 
boolean Fixed=false;
int Option;
void setup () {
  //Set initial state via dip switch, option A is 0, option B is 1
  if (Tn.pot()>0.5){
        Opinion=true;
  }
  else{
        Opinion=false;
  }
  
  if (Tn.dip1()==true){

         if(Tn.dip2()==true){
              Option=3;
         }
  }
  else{
         if(Tn.dip2()==true){

            Option=2;
          
         }
         else{
            Option=1;
         }
  }
  
    
}


void loop(){

  
  
  set_colour();

  for (int reps=1; reps<1000; reps++ ){
            check_potential();
        if (Tn.sw()==true){
            switchHold();
        }
              
              
       
         check_Reset();
        
       
         delay(1);
  }
  
 
  
  if(Option==1){
    Self_Majority_Vote();
  }
  else if(Option==2){
    Majority_Vote();
  }

  else if(Option==3){
    Neighbourhood_Consensus();
  }
  else{
    Tn.colour(255,0,0);
  }



  
  
}

void check_Reset(){

  if(Tn.masterSw()==true){

                if (Tn.pot()>0.5){
                      Opinion=true;
                }
                 else{
                       Opinion=false;
                }
                set_colour();
        }
}

void Majority_Vote (){

  double total=0;
  int connections=0;
  for (int input=0; input<6; input++){
    
      if(Tn.isConnected(input)==true){
        
          connections++;
          
          if(Tn.digitalRead(input)==true){
            
                total++;
                
          }
      }
        
  }
  
  if(connections!=0){
    
        total=total/(double)connections;
        
        if (total>0.5){
             Opinion=true;
        }
        if (total<0.5){
             Opinion=false;
             
        }
             
    
  }
  
  
  
}






void Self_Majority_Vote (){
  
  
  
  double total=0;
  if(Opinion==true){
    total=total+1;
  }
  int connections=1;
  for (int input=0; input<6; input++){
    
      if(Tn.isConnected(input)==true){
        
          connections++;
          
          if(Tn.digitalRead(input)==true){
            
                total++;
                
          }
      }
        
  }
  
  if(connections!=0){
    
        total=total/(double)connections;
        
        if (total>0.5){
             Opinion=true;
        }
        if (total<0.5){
             Opinion=false;
             
        }
             
    
  }
  


  
}


void Neighbourhood_Consensus(){

if (Opinion==false){
     Tn.colour(0,255,0);
     Tn.digitalWrite(false); 
  }
  else if (Opinion==true){
      Tn.colour(0,0,255);
      Tn.digitalWrite(true); 
  }

  double total=0;
  if(Opinion==true){
    total=total+1;
  }
  int connections=1;
  for (int input=0; input<6; input++){
    
      if(Tn.isConnected(input)==true){
        
          connections++;
          
          if(Tn.digitalRead(input)==true){
            
                total++;
                
          }
      }
        
  }
  
  if(connections!=0){
    
        
        
        if (total==0){
             Opinion=false;
        }
        if (total==connections){
             Opinion=true;
             
        }
             
    
  }
  
  
  

  
}

void switchHold(){
  
   int test=0;

   Opinion= !Opinion;
   set_colour();
   
   while(test==0){
     
    if(Tn.sw()==false){
       
       test=1;
     }
   }
   
}


void set_colour(){

   if (Opinion==false){
     Tn.colour(0,255,0);
     Tn.digitalWrite(false); 
  }
  else if (Opinion==true){
      Tn.colour(0,0,255);
      Tn.digitalWrite(true); 
  }
}

void check_potential(){

  while(Tn.pot()<0.1){
    flash();
  }
  while(Tn.pot()>0.9){
    flash();
    
  }


}

void flash(){

  Tn.colour(0,0,0);
  for (int reps=1; reps<500; reps++ ){
    check_Reset();
    if (Tn.sw()==true){
            switchHold();
        }
    
  delay(1);
  }

  set_colour();
  for (int reps=1; reps<500; reps++ ){
    check_Reset();
    if (Tn.sw()==true){
            switchHold();
        }
  delay(1);
  }

    
}

