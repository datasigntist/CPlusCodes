//
//  main.cpp
//  geneticAlgorithm
//
//  Created by vishwanathan raman on 03/12/19.
//  datasigntist@gmail.com
//  Copyright © 2019 vishwanathan raman. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

vector <vector<int>> crossoverAndMutationOperation(vector <vector<int>> &genePoolp, long minIndex, long maxIndex, int crossOverPoint)
{
    vector <vector<int>> children;
    vector <int> childInstance;
    int mutationPoint {0}, mutatedPoint {0};
    
    for(int outLoop{0};outLoop < 4; ++outLoop){
        for(int loop{0}; loop < 8; ++loop){
            
            if (outLoop==0)
            {
                if (loop > crossOverPoint)
                {
                    childInstance.push_back(genePoolp[minIndex][loop]);
                } else
                {
                    childInstance.push_back(genePoolp[maxIndex][loop]);
                }
                
            } else if (outLoop==1){
                
                if (loop > crossOverPoint)
                {
                    childInstance.push_back(genePoolp[maxIndex][loop]);
                } else
                {
                    childInstance.push_back(genePoolp[minIndex][loop]);
                }
                
            } else if (outLoop==2){
                
                if (loop > crossOverPoint)
                {
                    childInstance.push_back(genePoolp[maxIndex][loop-crossOverPoint]);
                } else
                {
                    childInstance.push_back(genePoolp[minIndex][loop]);
                }
                
            } else if (outLoop==3){
                
                if (loop > crossOverPoint)
                {
                    childInstance.push_back(genePoolp[minIndex][loop-crossOverPoint]);
                } else
                {
                    childInstance.push_back(genePoolp[maxIndex][loop]);
                }
                
            }
            
        }
        
        for (int inloop{0};inloop < 1; ++inloop)
        {
            mutationPoint = std::rand()%8;
            
            mutatedPoint = std::rand()%8;
            
//            cout << "mutationPoint "<< mutationPoint<<" mutatedPoint "<<mutatedPoint<<endl;
            
            childInstance[mutationPoint] = mutatedPoint;
        }
        
        
        children.push_back(childInstance);
        childInstance.clear();
        
    }
    
    return children;
}

int findTheNextBestChild(vector <double> &fitnessScoreList,long maxIndex)
{
    int indexOfChild {0};
    double totalFitnessSum {0};
    for(int loop{0}; loop < fitnessScoreList.size(); ++loop)
        totalFitnessSum = totalFitnessSum + fitnessScoreList[loop];
    

    for(int loop{0}; loop < fitnessScoreList.size(); ++loop){
        if (fitnessScoreList[loop] >= totalFitnessSum/fitnessScoreList.size() & fitnessScoreList[loop] < fitnessScoreList[maxIndex]) {
            
            indexOfChild = loop;
            break;
        }
            
    }
    
    return indexOfChild;
}

double getAverageFitnessScore(vector <double> &fitnessScoreList){
    
    double averageFitnessScore {0.0};
    
    for (int loop{0}; loop < fitnessScoreList.size(); ++loop)
    {
        averageFitnessScore = averageFitnessScore + fitnessScoreList[loop];
    }
    
    return averageFitnessScore/fitnessScoreList.size();
}

void printFitnessscores(vector <vector<int>> &genePool,vector <double> &fitnessScoreList)
{
    
    cout << endl << endl;
    
    for(int loop{0}; loop < genePool.size(); ++loop){
        for(int inLoop{0}; inLoop < genePool[loop].size(); ++inLoop){
            cout << genePool[loop][inLoop];
        }
        
        cout << " Fitness Score " << fitnessScoreList[loop] << endl;
    }
}

void printVector(vector <vector<int>> &genePool,long index)
{
    cout << endl;
    
    for (int outLoop{0} ; outLoop < 8 ; ++outLoop)
    {
        cout << genePool[index][outLoop];
    }
    
    cout << endl;
}

void printVector(vector <int> &fitnessScoreList)
{
    cout << endl;
    
    for (int outLoop{0} ; outLoop < fitnessScoreList.size() ; ++outLoop)
    {
        cout << fitnessScoreList[outLoop] << "\n";
    }
}

void printMatrix(vector <vector<int>> &chessBoardInstancep)
{
    for (int outLoop{0} ; outLoop < chessBoardInstancep.size() ; ++outLoop)
    {
        
        for(int inLoop{0}; inLoop < chessBoardInstancep[outLoop].size(); ++inLoop)
        {
            cout << chessBoardInstancep[outLoop][inLoop];
        }
        
        cout << endl;
    }
}

double calculateFitnessScore(int indexp, vector <vector<int>> &genePoolp, vector <vector<int>> &chessBoardInstancep,int debugp = 0)
{
    int conflictCount {0}, colNumber {0}, rowNumber {0}, rowPos {0};
    double fitnessScore {28.0};
    
    for(int column{0}; column < genePoolp[indexp].size(); ++column)
    {
        
        rowPos = genePoolp[indexp][column];

        if (debugp == 1)
          cout << rowPos << ";" << column << ";" << chessBoardInstancep[rowPos][column] << endl;
    
        
        /*Diagonally Down Right*/
        
        if (rowPos != 7 & column!=7){
            colNumber = column;
            if (debugp == 1)
                cout << "Diagonal Down Right" << endl;
            for(int inloop{rowPos+1};inloop < 8; ++inloop){
                colNumber++;
                if (colNumber>7)
                    break;
                if (debugp == 1)
                    cout << inloop << ";" << colNumber << endl;
                if (chessBoardInstancep[inloop][colNumber] == 1){
                    if (debugp == 1)
                        cout << "Conflict Spotted" << endl;
                    conflictCount++;
                }
          }
        }
        
        /*Diagonally Up Right*/
        
        if (rowPos != 0 & column!= 7){
              colNumber = column;
              if (debugp == 1)
                  cout << "Diagonal Up Right" << endl;
              for(int inloop{rowPos-1};inloop >= 0; --inloop){
                  colNumber++;
                  if (colNumber>7)
                      break;
                  if (debugp == 1)
                      cout << inloop << ";" << colNumber << endl;
                  if (chessBoardInstancep[inloop][colNumber] == 1){
                      if (debugp == 1)
                          cout << "Conflict Spotted" << endl;
                      conflictCount++;
                  }
            }
        }
        
        /*Diagonally Down Left*/
        
        if (rowPos != 7 & column != 0){
              rowNumber = rowPos;
              if (debugp == 1)
                  cout << "Diagonal Down Left" << endl;
              for(int inloop{column-1};inloop >= 0; --inloop){
                  rowNumber++;
                  if (rowNumber>7)
                      break;
                  if (debugp == 1)
                      cout << rowNumber << ";" << inloop << endl;
                  if (chessBoardInstancep[rowNumber][inloop] == 1){
                      if (debugp == 1)
                          cout << "Conflict Spotted" << endl;
                      conflictCount++;
                  }
            }
        }
        
        /*Diagonally Up Left*/
        
        if (rowPos!= 0 & column != 0){
              colNumber = column;
              if (debugp == 1)
                  cout << "Diagonal Up Left" << endl;
              for(int inloop{rowPos-1};inloop >= 0; --inloop){
                  colNumber--;
                  if (colNumber<0)
                      break;
                  if (debugp == 1)
                      cout << inloop << ";" << colNumber << endl;
                  if (chessBoardInstancep[inloop][colNumber]  == 1){
                      if (debugp == 1)
                          cout << "Conflict Spotted" << endl;
                      conflictCount++;
                  }
            }
        }
        /*Horizontal Right*/
          rowNumber = rowPos;
          colNumber = column;
          if (debugp == 1)
              cout << "Horizontal Right" << endl;
          for(int inloop{colNumber+1};inloop < 8; ++inloop){
              if (debugp == 1)
                  cout << rowNumber << ";" << inloop << endl;
              if (chessBoardInstancep[rowNumber][inloop] == 1){
                  if (debugp == 1)
                      cout << "Conflict Spotted" << endl;
                  conflictCount++;
              }
        }
        
        /*Horizontal Left*/
        if (column!=0){
              rowNumber = rowPos;
              colNumber = column;
              if (debugp == 1)
                  cout << "Horizontal Left" << endl;
              for(int inloop{colNumber-1};inloop >= 0; --inloop){
                  if (debugp == 1)
                      cout << rowNumber << ";" << inloop << endl;
                  if (chessBoardInstancep[rowNumber][inloop] == 1){
                      if (debugp == 1)
                          cout << "Conflict Spotted" << endl;
                      conflictCount++;
                  }
            }
        }
        
        if (debugp == 1)
            cout << "Conflict Count " << conflictCount << endl;
        
    }
    
    if (debugp == 1)
        cout << "Total Conflict Count " << conflictCount << endl;

    
    return (100*((fitnessScore-conflictCount)/28));
}

int main(int argc, const char * argv[]) {
    
    int populationSize {100}, crossoverPoint {3}, generationCount {10000}, generationLoop {0}, nextBestChild {0};
    long minIndex {0}, maxIndex {0};
    double fitnessScore {0.0};
    
    vector <vector<int>> genePool;
    /*{
        {5, 7, 1, 3, 0, 6, 4, 2},
        {2, 5, 3, 1, 7, 4, 6, 0},
        {3, 3, 6, 5, 0, 4, 7, 0}
    };*/
    
    vector <vector<int>> children;
    
    vector <int> genePoolInstance;
    
    vector <double> fitnessScoreList;
    
    vector <vector<int>> chessBoard
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    //Generate Random population
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    for (int loop{0}; loop<populationSize; ++loop){
        for (int count{0}; count < 8; ++count)
        {
            genePoolInstance.push_back(std::rand()%8);
        }
  
        if(std::count(genePool.begin(), genePool.end(), genePoolInstance)==0)
        {
            genePool.push_back(genePoolInstance);
        }
        
        genePoolInstance.clear();
    }
     
    vector <vector<int>> chessBoardInstance;
    
    for (int outLoop{0} ; outLoop < genePool.size() ; ++outLoop)
    {
        chessBoardInstance = chessBoard;
        for(int inLoop{0}; inLoop < genePool[outLoop].size(); ++inLoop)
        {
            chessBoardInstance[genePool[outLoop][inLoop]][inLoop] = 1;
        }
        
        fitnessScore =calculateFitnessScore(outLoop,genePool,chessBoardInstance,0);
        
        fitnessScoreList.push_back(fitnessScore);
    }
    
//    printFitnessscores(genePool,fitnessScoreList);
    
    do
    {
              
       minIndex = (std::min_element(fitnessScoreList.begin(),fitnessScoreList.end()) - fitnessScoreList.begin());
       maxIndex = (std::max_element(fitnessScoreList.begin(),fitnessScoreList.end()) - fitnessScoreList.begin());
    
       nextBestChild = std::rand()%fitnessScoreList.size();
//       cout << "Random number "<< nextBestChild << ",Size " << fitnessScoreList.size();
    
//       nextBestChild = findTheNextBestChild(fitnessScoreList, maxIndex);
        
//       printVector(genePool,maxIndex);
//       printVector(genePool,nextBestChild);
       
       children = crossoverAndMutationOperation(genePool,nextBestChild,maxIndex,crossoverPoint);
       
       for(int loop{0}; loop < children.size(); ++loop)
       {
           chessBoardInstance = chessBoard;
           for(int column{0}; column < children[loop].size(); ++column)
           {
               chessBoardInstance[children[loop][column]][column] = 1;
           }
           
           fitnessScore = calculateFitnessScore(loop,children,chessBoardInstance,0);
           
           if (fitnessScore >= getAverageFitnessScore(fitnessScoreList))
           {
               if(std::count(genePool.begin(), genePool.end(), children[loop])==0)
               {
  //                 cout << endl << "Does not exist, hence pushed" << endl;
                   genePool.push_back(children[loop]);
                   
                   fitnessScoreList.push_back(fitnessScore);
               }
           }
           
       }
        
//       printFitnessscores(genePool,fitnessScoreList);
   
       maxIndex = (std::max_element(fitnessScoreList.begin(),fitnessScoreList.end()) - fitnessScoreList.begin());
        

        cout << endl << "Generation " << generationLoop << ", Average Fitness Score " << getAverageFitnessScore(fitnessScoreList) << ", Length " << fitnessScoreList.size() << endl;
        
       generationLoop++;
        
   }while(generationLoop < generationCount & fitnessScoreList[maxIndex]<100);
    
    if (fitnessScoreList[maxIndex] >= 100)
    {
        cout << "Fitness Score " << fitnessScoreList[maxIndex];
        printVector(genePool,maxIndex);
    }
    
    return 0;
}
