/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package project1comp482;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author yups
 */
public class Project1COMP482 {

    private static Object[] filename;
    private static int totalPeopleInt = 0;

    /**
     * @param args the command line arguments
     */
    //GLOBAL PREFERENCE ARRAYS
    static int menPrefer[][];
    static int womenPrefer[][];
    //GLOBAL PERMUTATION ARRAY
    static int solution[];
    //Counter for how many stable matches
    static int counter;

    public static boolean findInWomen(int VIM, int MAN) {
        for (int k = 0; k < totalPeopleInt; k++) {
            //THIS IS GOING LEFT 2 RIGHT IN WOMAN MATRIX IN THE PASSED MAN (VIM)
            if (solution[VIM - 1] == womenPrefer[VIM - 1][k]) {
                //SOLUTION VALUE AND NUMBER IN WOMANS MATRIX ARE THE SAME THUS RETURN FALSE FOR NOBREAKUP
                return false;
            } //else if (Integer.compare((MAN+1), womenPrefer[VIM-1][k]) == 0){
            else if ((MAN + 1) == womenPrefer[VIM - 1][k]) {
                //PASSED MAN AND THE NUMBER IN WOMANS MATRIX ARE THE SAME THUS HIGHER ON BOTH PREFERED LISTS THUS RETURN TRUE FOR BREAKUP
                return true;
            } else {
                //PASSED MAN && SOLUTION MAN HAVE NO RELATION WITH ACCESSED VALUE
            }
        }
        return false;//DEFAULT RETURN NO BREAK UP

    }

    public static boolean findInMen(int[] solution) {//solution contains an array of the given permutation
        //This method goes left to right in the mens matrix 
        for (int i = 0; i < totalPeopleInt; i++) {
            //THIS IS GOING UP AND DOWN IN THE PREFERED MAN MATRIX
            outerloop:
            for (int j = 0; j < totalPeopleInt; j++) {//THIS IS GOING LEFT2RIGHT IN THE PREFERED MAN MATRIX
                if (menPrefer[i][j] == solution[i]) {
                    if ((findInWomen(menPrefer[i][j], i)) == true) {
                        //IF THE MAN THATS PASSED INTO THE WOMANS ARRAY IS HIT FIRST THAT MEANS THEY BOTH SHOULD BE WITH EACHOTHER THUS BREAKUP
                        return true;
                    } else {
                        //IF IT HITS THE WOMAN THATS PREFERED IN THE ARRAY FIRST THEN HIGHEST PREFERED IS SELECTED
                        //BREAK IS TO GO TO THE NEXT MAN AND ACCESS HIS PREFERENCES
                        break outerloop;
                    }
                } else if (menPrefer[i][j] != solution[j]) {
                    //ELSE IF IT DOESNT = THE WOMAN IN THE PERMUTATION ARRAY
                    if ((findInWomen(menPrefer[i][j], i)) == true) {
                        //IF THE MAN THATS PASSED INTO THE WOMANS ARRAY IS HIT FIRST THAT MEANS THEY BOTH SHOULD BE WITH EACHOTHER THUS BREAKUP
                        return true;
                    } else {
                        //IF ITS NOT THE PASSED MAN OR THE WOMAN IN THE SOLUTION THEN KEEP MOVING ON

                    }
                }
            }
        }
        return false;
    }

    public static void printAllRecursive(int n, int[] elements) {//This method generates
        //all the permutations of all possible solutions
        int[][] allOptions;
        if (n == 1) {
            if (findInMen(elements) == true) {
                //ANY TIME TRUE IS RETURNED THERES A BREAK UP
            } else {
                //ANY TIME FALSE MEANS NO BREAK UP THUS VALID SOLUTION UP COUNTER AND PRINT
                printArray(elements);
                counter++;
            }
        } else {
            //SWAP FOR PERMUTATIONS
            for (int i = 0; i < n - 1; i++) {
                printAllRecursive(n - 1, elements);
                if (n % 2 == 0) {
                    swap(elements, i, n - 1);
                } else {
                    swap(elements, 0, n - 1);
                }
            }
            printAllRecursive(n - 1, elements);
        }
    }

    private static void swap(int[] input, int a, int b) {//This helps assist the previous method in creating all possible permutations by
        //swaping values in the array
        int tmp = input[a];
        input[a] = input[b];
        input[b] = tmp;
    }

    private static void printArray(int[] input) {//HELPS PRINT THE SOLUTIONS STORED IN INT ARRAY
        for (int i = 0; i < input.length; i++) {
            System.out.print(input[i]);
        }
        System.out.println("");
    }

    private static int[] createTempArray(int total) {//HELPS GENERATE ARRAY SIZE TOTAL
        //AND CREATES AN ARRAY CONTAINING {1,2,...,total} ELEMENTS
        int[] tempArray = new int[total];
        for (int i = 0; i < total; i++) {
            tempArray[i] = (i + 1);
        }
        return tempArray;
    }

    public static void main(String[] args) {
        String totalPeople = null;
        String filename = "input1.txt";

        //FILE READING CODE
        try {
            try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
                String line;
                //GETS FIRST LINE SO I KNOW HOW TO SIZE MY ARRAYS AND MATRIX'S
                totalPeople = reader.readLine();
                totalPeopleInt = Integer.parseInt(totalPeople);
                //MATRIX SIZING
                menPrefer = new int[totalPeopleInt][totalPeopleInt];
                womenPrefer = new int[totalPeopleInt][totalPeopleInt];

                int slot = 1;
                //WHILE THERES NOTHING LEFT IN THE FILE
                while ((line = reader.readLine()) != null) {
                    if (slot <= totalPeopleInt) {//WHEN I GET TO ARRAY SLOT WITH HOW MANY PEOPLE I HAVE THAT WILL BE MEN MATRIX
                        //CONVERT FROM STRING ARRAY THATS BROKEN WITH " " AND THEN CONVERT TO INT ARRAY
                        String[] prefArray = line.split(" ", totalPeopleInt);
                        for (int i = 0; i < totalPeopleInt; i++) {
                            menPrefer[slot - 1][i] = Integer.parseInt(prefArray[i]);
                        }
                    } else if (slot > totalPeopleInt) {//ANYTHING ABOVE TOTAL PEOPLE INT WILL MEAN WOMAN MATRIX
                        String[] prefArray = line.split(" ", totalPeopleInt);
                        for (int i = 0; i < totalPeopleInt; i++) {
                            womenPrefer[slot - (totalPeopleInt + 1)][i] = Integer.parseInt(prefArray[i]);
                        }
                    }
                    slot++;
                }
            }
        } catch (IOException e) {
            System.err.format("Exception occured trying to read '%s'.", filename);
            e.printStackTrace();
        }
//CREATE TEMP ARRAY WITH TOTAL PEOPLE {1,2,...,TOTAL}
        solution = createTempArray(totalPeopleInt);
        //GENERATE PURMUTATIONS OF THAT ARRAY
        printAllRecursive(totalPeopleInt, solution);
        //COUNTER FOR HOW MANY STABLE MATCHES THE SET HAD
        System.out.println("Stable Matches: " + counter);
    }

}
