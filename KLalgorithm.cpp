#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

void inputValue();
void print2DVector(vector<vector<int> >& v2D);
void printVector(vector<int>& v);

int main (){
  inputValue();
  return 0;
}

void inputValue(){

  //***** Input File ******************************************************//
 
    
    string Vertices_2n;
    std::string line;
  	  
    ofstream outputfile ("output.txt");
    //opens the inputfile
    ifstream myfile;
    myfile.open ("inputproject.txt");
    getline (myfile,Vertices_2n);
    cout<<"total vertices:" << Vertices_2n << "\n";
    
    int Vertices_n = 0;
    int VerticesInt_2n = atoi(Vertices_2n.c_str()) ;
    Vertices_n = VerticesInt_2n /2; // No of vertices in each partition
    int size = VerticesInt_2n;      // Total no. of nodes (2n)
    
     
    // Declaring Vectors and arrays
     
     std::vector< std::vector<int> > main_matrix;    // main matrix to hold file contents after parsing
     std::vector< std::vector<int> > matrix;
      std::vector<int> PreVecter;             // Vector used for initial partitioning
      std::vector<int> InitialA;            // to hold partition1
     std::vector<int> InitialB;            // to hold partition2
     std::vector<int> partition1;            // to hold partition1
     std::vector<int> partition2;            // to hold partition2
     std::vector<int> Itr_partition1;            // to hold partition1
     std::vector<int> Itr_partition2;            // to hold partition2
     
    std::vector< vector<int> > gainVector;   
    std::vector< std::vector<int> > dvalue;
    std::vector<int> Xvector;
    std::vector<int> Yvector;
    std::vector<int> PartialSum;
    std::vector<int> Gk;
    int stepGain[5] = {0};
    int cost[50][50] = {0}; // value has to be input for size of cost matrix
    int CostExt;
    int k=0;
    int iteration = 1;
    //int step = 0;
    
    int Gkmax;
    
    
    
    
// Main Matrix from Input file 

    while (myfile)
              {
                    string s;
                    int a;
                    if (!getline( myfile, s )) break;
                
                    istringstream ss( s );
                    vector <int> record;
                
                    while (ss)
                    {
                      string s;
                      if (!getline( ss, s, ',' )) break;
                      stringstream(s) >> a;
                      record.push_back( a );
                    }
                
                    main_matrix.push_back( record );
                    
              }
              main_matrix.resize(size);    


// printing the main vector matrix array  & pushing in vecter prevecter for partition array. 
        for( int i=0; i < main_matrix.size(); i++ ) 
		{
           for( int j=0; j < main_matrix[i].size(); j++ ) 
		   {
     	   		PreVecter.push_back( main_matrix[i][j]);
           }
        }
   
//sorting Prevector in ascending order.
     sort(PreVecter.begin(),PreVecter.end() );
      
//eliminates repeating nodes  (has error as the produces a last redundant integer value)
    
  PreVecter.erase(std::unique(PreVecter.begin(), PreVecter.end()), 
  PreVecter.end());
      PreVecter.pop_back();
      // Creating Initial Partition     
            
         for( int i=0; i<=PreVecter.size(); i++ ) 
            {
                   
                        if(PreVecter[i]<= Vertices_n) 
                        {
                              InitialA.push_back(PreVecter[i]);
                        }
                        else if (PreVecter[i]> Vertices_n)
                        {
                            InitialB.push_back(PreVecter[i]);
                        }
            } 
         
            partition1 = InitialA; 
      
            partition2 = InitialB;         
            
             

do
{ 
       //cout << "********* Iteration Step *****************************************************" <<endl;
       
       
       
         outputfile<< "Iteration number" << iteration << endl;
       matrix = main_matrix; // copy of the main matrix 
      Itr_partition1.clear();
      Itr_partition2.clear(); 
       Itr_partition1 = partition1;
       Itr_partition2 = partition2;
       
      int steps = 1;
      
      PartialSum.clear();
      Xvector.clear();
      Yvector.clear();
      gainVector.clear();
      Gk.clear();
      dvalue.clear();
      
      while(steps <= Vertices_n)
      {    
          
	  
//         cout << "********* Step "<<steps <<  "*****************************************************" <<endl; 
  //          cout << endl;
            
            
           for( int i=0; i < matrix.size(); i++ ) // Adjust matrix.size() value
            {
                //cout << "Matrix: " << matrix[i][0] << endl;
                std::vector <int> vi;
                vi.push_back(matrix[i][0]); 
                
                      if(std::find(partition1.begin(), partition1.end(), matrix[i][0]) != partition1.end()) 
                     { 
                          int internalEdge = 0;
                          int externalEdge = 0; 
                                          
                          for( int j=1; j<matrix[i].size(); j++ ) {
                                if( std::find(partition2.begin(), partition2.end(), matrix[i][j])!=partition2.end())
                                {
                                  
                                    externalEdge = externalEdge + 1;
                                }
                                else if( std::find(partition1.begin(), partition1.end(), matrix[i][j])!=partition1.end())
                                {
                                  
                                    internalEdge = internalEdge + 1;         
                                }
                                   
                          }
                                   vi.push_back(externalEdge); 
                                   vi.push_back(internalEdge); 
                                   vi.push_back(externalEdge - internalEdge);
                                   dvalue.push_back( vi );
                      }
                      else if(std::find(partition2.begin(), partition2.end(), matrix[i][0]) != partition2.end()) 
                     { 
                          int internalEdge = 0;
                          int externalEdge = 0; 
                          for( int j=1; j<matrix[i].size(); j++ ) {
                                if( std::find(partition1.begin(), partition1.end(), matrix[i][j])!=partition1.end())
                                {
                                    
                                     externalEdge = externalEdge + 1;
                                }
                                else if( std::find(partition2.begin(), partition2.end(), matrix[i][j])!=partition2.end())
                                {
                                
                                    internalEdge = internalEdge + 1; 
                                    
                                }
                                   
                          }
                                   vi.push_back(externalEdge); 
                                   vi.push_back(internalEdge); 
                                   vi.push_back(externalEdge - internalEdge);
                                   dvalue.push_back( vi );
                      }
                      
              }
                         
                // Building Cost Adjacency Matrix
                                     
                          for( int i=0; i < matrix.size(); i++ )
                            {
                                    for( int j=0; j<matrix[i].size(); j++ ) 
                                          {
                                                
                                                int rowval = matrix[i][0];
                                                int colval = matrix[i][j]; 
                                                cost[rowval][colval] = 1;
                                                if ( rowval == colval) 
                                                
                                               { cost[rowval][colval] = 0;}
                                    }
                            }
                                                   
                            
                // Compute gain values for each possible swap       
               
            int gaintotal = 0; 
           
            for( int i=0; i < dvalue.size() ; i++ ) // Adjust matrix.size() value
            {
                std::vector <int> vi;
                      if(std::find(partition1.begin(), partition1.end(), dvalue[i][0]) != partition1.end()) 
                     { 
                          for( int j=0; j<dvalue.size() ; j++ )
                           {
                                if( std::find(partition2.begin(), partition2.end(), dvalue[j][0])!= partition2.end())
                                {
                                 
                                    gaintotal = dvalue[i][3] + dvalue [j][3] - 2*cost[dvalue[j][0]][dvalue[i][0]];
                                    vi.push_back(dvalue[i][0]); 
                                   vi.push_back(dvalue[j][0]); 
                                   vi.push_back(gaintotal);
                                   gainVector.push_back( vi );
                                   vi.clear();
                                }
                                
                                   
                          }
                                   
                      }
                     
                     }           
                     
                     
                 // Finding max gain 
                 
                         int max = gainVector[0][2];
                         int maxRowValue = gainVector[0][0];
                         int maxColValue = gainVector[0][1];
                 
                 for (int i=1; i<gainVector.size(); i++)
                         {
                             
                            if (max < gainVector[i][2])
                                {
                                    max = gainVector[i][2];
                                    maxRowValue = gainVector[i][0];
                                    maxColValue = gainVector[i][1];
                                }
                         }
                             
                     
                // Swap pair of nodes [ai, bi]         
                            
                int swapNode1 = 0;
                int swapNode2 = 0;
                          
                         for(int i = 0; i < partition1.size(); i++)
                          {  
                                 if(partition1[i] == maxRowValue)
                                     {   
                                      //key found at index i
                                      swapNode1 =  i;
                                      break;
                                      }
                                      
                          }
                          
                          for(int j = 0; j < partition2.size(); j++)
                          {  
                                 if(partition2[j] == maxColValue)
                                      {   
                                      swapNode2 =  j;
                                      break;
                                      }   
                                 
                          }
                         
                         
                         
                         // Swap pair [ai,bi]. Lock vertices in 2 vectors- Xvector = {a1, a2, a3 .. an}
                         // Yvector = {b1, b2, b3 .. bn}
                         
                         swap(partition1[swapNode1], partition2[swapNode2]);
                         Yvector.push_back(partition1[swapNode1]);
                         Xvector.push_back(partition2[swapNode2]);
                                      
                        
                       // Compute partial gain sum 
                       
                      
                         PartialSum.push_back(max);   
                        
                        // delete rows of [ai bi] from matrix
                     
                         
                         for(int i = 0; i< matrix.size(); i++)
                         { 
                          if (matrix[i][0] == maxRowValue)
                          {
                            matrix.erase(matrix.begin()+ i );
                          }
                          
                         }
                    
                         
                          for(int j = 0; j< matrix.size(); j++)
                         { 
                          if (matrix[j][0] == maxColValue)
                          {
                            matrix.erase(matrix.begin()+ j );
                          }
                          
                         }
                    
                         
                          
                        
                                // increment steps
                          steps = steps +1; // condition for one iteration (steps < = vertices_n)
                                //clear vectors
                          dvalue.clear();
                          gainVector.clear();
                           sort(partition1.begin(),partition1.end() );
                          sort(partition2.begin(),partition2.end() ); 
        } // inner while loop ends


//<--------------------checking for the next iteration ----------> 
		
int sum =0;		

for (int k = 0; k < steps-1 ; k++)
{
    
     sum = sum + PartialSum[k];
     Gk.push_back(sum);
     
}

				
int result = *max_element(Gk.begin(), Gk.end());


//finding Gk max

Gkmax = Gk[0];
int Gkposition =0;

for (int i=0; i<Gk.size(); i++)
         {
             
            if (Gkmax < Gk[i])
                {
                    Gkmax = Gk[i];
                    Gkposition = i;
                }
         }	
// Swap back from X and Y

            partition1 = Itr_partition1;
      
            partition2 = Itr_partition2; 

 
            
            int swapNode1 = 0;
            int swapNode2 = 0;
  
   for(int k = 0; k <= Gkposition; k++)
   {
           for(int i = 0; i < partition1.size(); i++)
          {  
                 if( Xvector[k] == partition1[i] )
                     {   
                      //key found at index i
                      swapNode1 =  i;
                     
                      for(int j = 0; j < partition2.size(); j++)
                      {  
                                 if( Yvector[k] == partition2[j] )
                                      {   
                                          swapNode2 =  j;
                                          swap(partition1[swapNode1], partition2[swapNode2]);
                                         
                                      }   
                            
                      }
                      }
          }
          
             
   }
         
         
         
         // Swap pair [ai,bi]. Lock vertices in 2 vectors- Xvector = {a1, a2, a3 .. an}
         // Yvector = {b1, b2, b3 .. bn}
           sort(partition1.begin(),partition1.end() );
                          sort(partition2.begin(),partition2.end() );
          
          //printing on the output file
         outputfile << "Partition 1: [ " ;
         for( int i=0; i<partition1.size(); i++ ) {
                           
                                outputfile << partition1[i] << " ";
                               
         }
         outputfile << "] " << endl  ;
         outputfile << "Partition 2 : [" ;
         for( int i=0; i<partition2.size(); i++ ) {
                           
                                outputfile << partition2[i] << " ";
                               
         }
         outputfile << "] " << endl << endl ;
         
         
         //Cost of Partition
         int cutset =0;

          for( int i=0; i < main_matrix.size(); i++ )
            {
                                    
                      if(std::find(partition1.begin(), partition1.end(), main_matrix[i][0]) != partition1.end()) 
                      { 
                          
                         
                                          
                          for( int j=1; j<main_matrix[i].size(); j++ ) 
                          {
                                if( std::find(partition2.begin(), partition2.end(), main_matrix[i][j])!=partition2.end())
                                {
                                  
                                    cutset = cutset + 1;
                                }
                                
                                   
                          }
                                   
                       }
                      else if(std::find(partition2.begin(), partition2.end(), main_matrix[i][0]) != partition2.end()) 
                     { 
                          
                          
                          for( int j=1; j<main_matrix[i].size(); j++ ) 
                          {
                                if( std::find(partition1.begin(), partition1.end(), main_matrix[i][j])!=partition1.end())
                                {
                                    
                                    cutset = cutset + 1;
                                }
                               
                                   
                          }
                                  
                      }
                      
              }
;
outputfile << "Cost of Partition : " << cutset/2 << endl << endl ;          
 iteration = iteration +1;        
         
}while(Gkmax > 0 );		
  
int final_cutset =0;


 myfile.close();
outputfile.close();        
               
}







void print2DVector(vector<vector<int> >& v2D)
{
     for( int i=0; i < v2D.size(); i++ ) {
                            for( int j=0; j < v2D[i].size(); j++ ) {
                                cout << v2D[i][j];
                                
                            }
                             cout << endl ;
                                   
     }
}
void printVector(vector<int>& v)
{
       for( int i=0; i<v.size(); i++ ) {
                           
                                cout << v[i] << " ";
                               
                    }
                    cout << endl << endl ;
}


