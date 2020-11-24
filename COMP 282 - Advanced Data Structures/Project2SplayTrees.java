package project2splaytrees;

import java.util.concurrent.TimeUnit;

public class Project2SplayTrees {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("Splay Tree Insertion and Deletion Timer\n");
        System.out.println("      Ins & Del");
        long insertionTime = 0, deletionTime = 0;
        long insertionTotal = 0, deletionTotal = 0;
        insertionTime = insertionTimerFunction(100);
        deletionTime = deletionTimerFunction(100);
        System.out.println("100:    " + insertionTime + "ms " + deletionTime + "ms");
        insertionTotal = insertionTotal + insertionTime;
        deletionTotal = deletionTotal + deletionTime;
        insertionTime = insertionTimerFunction(1000);
        deletionTime = deletionTimerFunction(1000);
        System.out.println("1000:   " + insertionTime + "ms " + deletionTime + "ms");
        insertionTotal = insertionTotal + insertionTime;
        deletionTotal = deletionTotal + deletionTime;
        insertionTime = insertionTimerFunction(10000);
        deletionTime = deletionTimerFunction(10000);
        System.out.println("10000:  " + insertionTime + "ms " + deletionTime + "ms");
        insertionTotal = insertionTotal + insertionTime;
        deletionTotal = deletionTotal + deletionTime;
        insertionTime = insertionTimerFunction(100000);
        deletionTime = deletionTimerFunction(100000);
        System.out.println("100000: " + insertionTime + "ms " + deletionTime + "ms");
        insertionTotal = insertionTotal + insertionTime;
        deletionTotal = deletionTotal + deletionTime;
        System.out.println("Total:  " + insertionTotal + "ms " + deletionTotal + "ms");
    }

    public static long insertionTimerFunction(int numItems) {
        long startTime, endTime, duration;
        SplayTree tree = new SplayTree();
        startTime = System.nanoTime();
        for (int i = 0; i < numItems; i++) {
            tree.insert(i);
        }
        endTime = System.nanoTime();
        duration = ((endTime - startTime) / 1000000);
        return duration;
    }

    public static long deletionTimerFunction(int numItems) {
        long startTime, endTime, duration;
        SplayTree tree = new SplayTree();
        for (int i = 0; i < numItems; i++) {
            tree.insert(i);
        }
        startTime = System.nanoTime();
        for (int i = 0; i < numItems; i++) {
            tree.delete(i);
        }
        endTime = System.nanoTime();
        duration = ((endTime - startTime) / 1000000);
        return duration;
    }
}