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
//ECE 528
//Tenzin Ngodup
//KL Partioning Software
// PART II 
// OCT 22/2013
//     Consider a Graph G(V,E) = undirected connected graph.
//     2n = Total number of Vertices 
//     {P1,P2} = Two equal size partition of vertices
//Main Function

int main (){

  cout << "KL Programming Step 1 \n " << endl ;
  cout << "Iteration Number: 1 \n " << endl ;
  inputValue();
   
  return 0;
}

void inputValue(){
    
    string Vertices_2n;
    //opens the inputfile
    ifstream myfile;
    myfile.open ("input.txt");
    getline (myfile,Vertices_2n);
    cout<<"total vertices:" << Vertices_2n << "\n";
    int Vertices_n;
    int VerticesInt_2n = atoi(Vertices_2n.c_str()) ;
    Vertices_n = int(VerticesInt_2n)/2;
     vector< vector<int> > matrix; // to hold everything.
     std:: vector<int> PreVecter;
     std::vector<int> partition1;           // to hold partition1
     std::vector<int> partition2;            // to hold partition2
    std::string line;
    std::vector< vector<int> > cValue;
       //std::vector< vector<int> > cost;
    std::vector< vector<int> > gainVector( 5, std::vector<int>(5)); 
    int cost[11][11] = {0};
    std::vector< std::vector<int> > dvalue;
    int CostExt = 0;
    int CostInt = 0;

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
                
                    matrix.push_back( record );
              }
    


       // printing the main vector matrix array  & pushing in vecter prevecter for partition array. 
        for( int i=0; i < matrix.size(); i++ ) {
                            for( int j=0; j < matrix[i].size(); j++ ) {
                                
                                PreVecter.push_back( matrix[i][j]);
                                  }
       }
         print2DVector(matrix);
        
        
      /*  
         // sorting the main vector array for partition 
         for( int i=0; i < matrix.size(); i++ ) {
                            for( int j=0; j < matrix[i].size(); j++ ) {
                                PreVecter.push_back( matrix[i][j]);
                                  }
                                   
         }
         */                 
                   cout << "Pre-sorting state:" << endl;
                    //sort function
                   sort(PreVecter.begin(),PreVecter.end() );
                  
                    //eliminates repeat  (has error as the produces a last redundant integer value)
               PreVecter.erase(std::unique(PreVecter.begin(), PreVecter.end()), PreVecter.end());
                  PreVecter.pop_back();
                  

                 printVector(PreVecter); 
                    
                 for( int i=0; i<=PreVecter.size(); i++ ) {
                           
                                cout << PreVecter[i] << " ";
                                if(PreVecter[i]<= Vertices_n) 
                                {
                                      partition1.push_back(PreVecter[i]);
                                }
                                else if (PreVecter[i]> Vertices_n)
                                {
                                     partition2.push_back(PreVecter[i]);
                                }
                    } 
                    cout << endl << endl ;
                    cout <<"\n" << "Partition 1" << "\n";
                    printVector(partition1);
                    
                    cout <<"\n"  << "Partition 2" << "\n";
                    printVector(partition2);       
                   
                   
             //    Part for finding the cost partition    
             // If (first element is in parititon 1 & any element is in parition2) 
            //                cost added
            //  else if ( first element is in partition 2 & any element is in partion 1)
             //                   cost added
          
           
           for( int i=0; i < matrix.size(); i++ )
            {
                cout << "Matrix: " << matrix[i][0] << endl;
                std::vector <int> vi;
                vi.push_back(matrix[i][0]); 
                     if(std::find(partition1.begin(), partition1.end(), matrix[i][0]) != partition1.end()) 
                     { 
                          int internalEdge = 0;
                          int externalEdge = 0; 
                                          
                          for( int j=1; j<matrix[i].size(); j++ ) {
                                if( std::find(partition2.begin(), partition2.end(), matrix[i][j])!=partition2.end())
                                {
                                    CostExt = CostExt + 1;
                                    externalEdge = externalEdge + 1;
                                   // cost[i][j] = 1;
                                   // cost[j][i] = 1;
                                    
                                    
                                }
                                else if( std::find(partition1.begin(), partition1.end(), matrix[i][j])!=partition1.end())
                                {
                                    CostInt = CostInt + 1;
                                    internalEdge = internalEdge + 1; 
                                //     cost[i][j] = 1;
                                //    cost[j][i] = 1;
                                    
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
                                    CostExt = CostExt + 1;
                                     externalEdge = externalEdge + 1;
                                }
                                else if( std::find(partition2.begin(), partition2.end(), matrix[i][j])!=partition2.end())
                                {
                                    CostInt = CostInt + 1;
                                    internalEdge = internalEdge + 1; 
                                    
                                }
                                   
                          }
                                    vi.push_back(externalEdge); 
                                   vi.push_back(internalEdge); 
                                   vi.push_back(externalEdge - internalEdge);
                                   dvalue.push_back( vi );
                      }
                      
         }
         
         
            /*   xvalue -->    0 1 2 3 4 5 ........2n-1
                               1 2 3 4 5 6 ......  2n
            yvalue       0  1 [                      ]
              |          1  2 [                      ]
              |          2  3 [                      ]
              V          3  . [                      ]
                            . [                      ]
                      2n-1  2n[                      ] 
                  */
         
          for( int i=0; i < matrix.size(); i++ )
            {
                    for( int j=0; j<matrix[i].size(); j++ ) 
                          {
                                
                                int rowval = matrix[i][0];
                                int colval = matrix[i][j]; 
                                cost[rowval][colval] = 1;
                                if ( rowval = colval) 
                                
                               { cost[rowval][colval] = 0;}
                    }
            }
         
         cout<< "dvalue size" << dvalue.size() << endl;
         int p =0;
         int q =0;
         int k = 0, l = 0;
          
          
          for( int i=0; i < dvalue.size()/2; i++ )
            {
                   //if(std::find(partition1.begin(), partition1.end(), dvalue[i][0]) != partition1.end()) 
                    // { 
                          
                                  
                          for( int j= dvalue.size()/2; j<(dvalue.size()-1); j++ ) 
                            {
                              
                               k = dvalue[j][0]; 
                               l = dvalue[i][0];
                           
                               cout<< dvalue[i][3] <<" " << dvalue [j][3] << " "  << cost[k][l] << endl;
                               
                               gainVector[p][q] = dvalue[i][3] + dvalue [j][3] - 2*cost[k][l]; 
                               
                               q=q+1;
                               
                          }
                  p=p+1;                
            }
            
             cout<<"gainVector" <<endl;
             print2DVector(gainVector);
         
          cout << endl << "dvalue" << endl;
          print2DVector(dvalue);
          cout << endl << "cvalue" << endl;
          
        // ofstream outfile;
        // outfile.open("output.txt");
         //outfile << "Cost of Partition External: " << object1.internal << endl << endl;
          //outfile << "Cost of Partition Internal: " << object1.external << endl << endl;
          cout << "Cost of Partition External: " << CostExt << endl << endl;
          cout << "Cost of Partition Internal: " << CostInt << endl << endl;
          cout << "Cost " <<" ";
          cout << endl;
            for (int i = 0; i < 11; ++i)
                 {
                            for (int j = 0; j < 11; ++j)
                            {
                                cout << cost[i][j] << ' ';
                            }
                            cout << endl;
                }
                
       system ("pause");
  
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

