package project2comp482;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class Project2COMP482 {
    static String filename = "input2.txt";
    static int[][] adjMatrix;
    static int matrixSize;
    static String loop = "There is no loop.";
    static int loopTrigger;
    static int[] parent;
    static boolean[] dfsVisited;
    static Stack<Integer> cycleStack = new Stack();

    public static void loadMatrix(int rowCounter, String[] tempArray) {
        // LOADS OUR MATRIX FROM THE ARRAYS PASSED FROM FILE
        for (int i = 0; i < matrixSize; i++) {
            adjMatrix[rowCounter][i] = Integer.parseInt(tempArray[i]);
        }
    }

    public static void dfsNodeValue(int row) {// PASS PARENT ROW
        for (int i = 0; i < matrixSize; i++) {// LEFT 2 RIGHT GET ADJ CHILDREN
            if ((adjMatrix[row][i] == 1) && (dfsVisited[i] == false)) {// IF IT IS THE CHILD OF THE PARENT
                // && HAS NOT BEEN VISITED
                dfsVisited[i] = true;// MARK VISITED
                parent[i] = row;// MARK PARENT OF THIS IS THE ONE THATS PASSED
                cycleStack.add(i);// PUSH TO STACK
            } else if ((adjMatrix[row][i] == 1) && (dfsVisited[i] == true)) {// IF SHOULD BE PARENT
                // && HAS ALREADY BEEN VISITED
                int parentValue = parent[i];
                if (parent[row] == -1) {// THIS APPLIES FOR THE FIRST NODE
                    // DO NOTHING
                } else if (parent[row] == (i)) {
                    // IF IT MATCHES THEN MOVE ALONG
                } else {
                    // IF ITS BEEN VISITED AND LAST PARENT DOESNT MATCH
                    // PARENT THATS STORED THEN
                    loop = "There is a loop.";
                }
            }
        }
    }

    public static void dfs() {// VISTED BOOL ARRAY AND PARENTS OF EACH NODE ARRAY
        dfsVisited = new boolean[matrixSize];
        parent = new int[matrixSize];
        Arrays.fill(parent, -1); // FILL -1 BY DEFAULT CAUSE WERE STARTING AT 0
        Arrays.fill(dfsVisited, false);
        cycleStack.push(0);// PUSH NODE 1
        dfsVisited[0] = true;// NODE 1 HAS BEEN VISITED
        while (cycleStack.isEmpty() != true) {
            // POP OBJECT /STORE VALUE/ AND GET ADJ CHILDREN
            int prevNode = cycleStack.pop();
            dfsNodeValue(prevNode); // GETS CHILDREN
        }
        System.out.println(loop);
    }

    public static void bfs() {
        // COUNTER FOR HOW MANHY LAYERS
        int counter = 0;
        boolean[] visited = new boolean[matrixSize]; // VISITED BOOL ARRAY SO NO REPEATS
        Queue<Integer> queue = new LinkedList();// QUEUE CAUSE BFS FIFO
        int[] layer = new int[matrixSize]; // ARRAY TO REMEMBER EACH LAYER
        Arrays.fill(layer, 0);// DEFAULT FILL
        Arrays.fill(visited, false);
        queue.add(0);// ADD NODE 1
        visited[0] = true; // NODE 1 VISITED
        layer[0] = 0; // 0 LAYER
        while (queue.isEmpty() != true) {// POP FIRST OBJECT
            int nodeValue = queue.poll();
            for (int i = 0; i < matrixSize; i++) {// L2R ACCESSMENT
                if (visited[i] == false && adjMatrix[nodeValue][i] == 1) {
                    // IF HAS NOT BEEN VISITED THEN AND IS A CHILD OF POPPED OBJECT
                    layer[i] = layer[nodeValue] + 1;
                    // NEXT LAYER ADD OBJECTS AND ADD TO QUEUE
                    queue.add(i);
                    // MARK AS VISITED
                    visited[i] = true;
                }
            }
        }
        for (int i = 0; i < matrixSize; i++) {
            // HELPS US MANAGE COUNTER TO HAVE HIGHEST VALUE OF LAYERS
            if (layer[i] > counter) {
                counter = layer[i];
            }
        }
        System.out.println("Layers: " + counter);
    }

    public static void main(String[] args) {
        try {
            String line;// THIS IS THE FILE READER
            int rowIndex = 0;
            BufferedReader reader = new BufferedReader(new FileReader(filename));
            reader.mark(1);// USES THIS TO MARK THE FIRST INDEX OF THE FILE JUST LEARNED ABOUT THIS
            matrixSize = reader.readLine().split(" ").length;// GATHERS HOW MANY OBJECTS IN A LINE OF THE FILE
            adjMatrix = new int[matrixSize][matrixSize];// CREATED MATRIX WITH GIVEN LENGTH
            reader.reset();// RESETS FILE TO MARK 1 REGATHER DATA
            while ((line = reader.readLine()) != null) {// LOADS ARRAY
                String[] lineArray = line.split(" ");
                loadMatrix(rowIndex, lineArray);
                rowIndex++;
            }
        } catch (IOException e) {
            System.err.format("Exception occured trying to read '%s'.", filename);
            e.printStackTrace();
        }
        // CALL DFS 1ST FOR FINDING LOOP
        dfs();
        // CALLS BFS FOR FINDING LAYERS
        bfs();
    }
}
