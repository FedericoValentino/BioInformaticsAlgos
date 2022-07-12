#include<stdio.h>
#include <stack>

#define EDGES 5

#define DIRECTED_GRAPH false

//Hierholzer's algorithm
int main()
{
    int graph[EDGES][EDGES] = {
            {0,1,1,1,0},
            {1,0,1,1,0},
            {1,1,0,1,1},
            {1,1,1,0,1},
            {0,0,1,1,0}
    };

    std::stack<int> tpath;
    std::stack<int> epath;

    tpath.push(0);
    int currentVertex;


    bool finished = false;
    while(!finished)
    {
        currentVertex = tpath.top();
        printf("currentVertex = %d\n", currentVertex);

        int visited = 0;
        for(int i = 0; i < EDGES; i++)
        {
            if(graph[currentVertex][i] == 0)
            {
                visited++;
            }
            else
            {
                printf("going to %d\n", i);
                graph[currentVertex][i]--;
                if(!DIRECTED_GRAPH)
                {
                    graph[i][currentVertex]--;
                }
                tpath.push(i);
                break;
            }

            if(visited == EDGES)
            {
                printf("pushing %d to epath\n", currentVertex);
                epath.push(currentVertex);
                tpath.pop();
            }
        }


        if(tpath.empty())
        {
            finished = true;
        }
    }


    while(!epath.empty())
    {
        printf("%d\n", epath.top());
        epath.pop();
    }
}