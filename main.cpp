//
//  main.cpp
//  Project3
//
//  Created by Nguyen Truong Duy Khang on 4/6/21.
//

#include <iostream>
#include<fstream>
#include <vector>
#include <string>
#include <sstream>
#include "graph.h"
#include "util.h"
#include "heap.h"
#include <climits>
using namespace std;
Graph readGraph(string graphFile, string direction) {
    int n;
    int m;
    int u;
    int v;
    float w;
    string token;
    vector<string> vertexEdge;
    vector<string> vertexInfo;
    //string path = "/Users/nguyentruongduykhang/Downloads/network_files/";
    //string filePath = path + graphFile;
    ifstream ifile(graphFile);
    string line;
    //Check if the file can be opened
    if (ifile.is_open()) {
        getline(ifile,line);
        vertexEdge = split_string(line);
        n = stoi(vertexEdge[0]);
        m = stoi(vertexEdge[1]);
        Graph graph(n,m);
        while (getline(ifile,line)) {
            vertexInfo = split_string(line);
            u = stoi(vertexInfo[1]);
            v = stoi(vertexInfo[2]);
            w = stof(vertexInfo[3]);
            if (direction.compare("directed") == 0) {
                graph.addDirectedEdge(u,v,w);
            } else {
                graph.addUnDirectedEdge(u, v, w);
            }
            
        }
        ifile.close();
        return graph;
        
        
    }
    else {
        cout<<"Error: cannot open file for reading"<<"\n";
        return Graph();
    }
}
int Flag;
int main(int argc, char** argv) {
    ofstream myfile ("myoutput.txt");
    Graph graph = readGraph(argv[1],argv[2]);
    string inputLine;
    vector<string>commandDetail;
    string command;
    vector<int>path;
    int source;
    int des;
    int result;
    bool valid = false;
    while(1) {
        getline(cin,inputLine);
        commandDetail = split_string(inputLine);
        command = commandDetail[0];
        if (command.compare("find") == 0) {
            cout<<"Query: "<<inputLine<<"\n";
            try {
                source = (int) stol(commandDetail[1]);
                des =  (int) stol(commandDetail[2]);
                Flag = stoi(commandDetail[3]);
            } catch (invalid_argument) {
                printf("Error: invalid find query\n");
            }
            catch(out_of_range) {
                printf("Error: invalid find query\n");
            }
            
            if (source < 0 || source > graph.sizeV || des == source || Flag > 1 || Flag < 0 ) {
                printf("Error: invalid find query\n");
                valid = false;
                continue;
            }
            valid = true;
            result = dijkstra_SP(graph,source, des);
            continue;
        }
        else if (command.compare("write") == 0) {
            cout<<"Query: "<<inputLine<<"\n";
            if (!valid) {
                cout<<"Error: no path computation done\n";
                continue;
            }
            if (stoi(commandDetail[2]) != source || (stoi(commandDetail[3]) < 0 || stoi(commandDetail[3]) > graph.sizeV)) {
                cout<<"Error: invalid source destination pair\n";
                continue;
                
            }
            source = stoi(commandDetail[2]);
            des = stoi(commandDetail[3]);
            if (des != source && graph.V[des]->d != INT_MAX) {
                path = findRoute(graph, source, des);
                if (graph.V[des]->color.compare("grey") == 0) {
                    cout<<"Path not known to be shortest: ";
                    //print path
                    //print out the weight of the path
                    printPath(path);
                    printPathWeight(graph, des);
                    continue;
                }
                
                cout<<"Shortest path: ";
                //print path
                //print out the weight of the path
                printPath(path);
                printPathWeight(graph, des);
                
                
            } else {
                if (result == 0) {
                    printf("No %d-%d path has been computed.\n",source,des);
                } else {
                    printf("No %d-%d path exists.\n",source,des);
                    
                }
            }
        }
        else if (command.compare("stop") == 0) {
            cout<<"Query: "<<inputLine<<"\n";
            //Free memory-new feature
            for (int i = 0; i < graph.size; i++) {
                delete graph.A[i];
            }
            for (int i = 0; i <graph.sizeV;i++) {
                delete graph.V[i];
            }
            delete[] graph.A;
            delete [] graph.V;
            exit(0);
        }
        
        
    }
    
    
    
}
