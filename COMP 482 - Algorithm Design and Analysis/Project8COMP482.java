/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package project8comp482;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author yups
 */
public class Project8COMP482 {

    public static int factorial(int tempInt) {///FACTORIAL CALCULATOR 5! = 5*4*3*2*1
        if (tempInt == 0) {
            return 1;
        }
        return tempInt * factorial(tempInt - 1);
    }

    public static long comb(int n, int r) {/// COMBINATION FORMULA C(n,r) = N! / (R!*(N-R)!)
        return (factorial(n) / (factorial(r) * factorial(n - r)));
    }

    public static void main(String[] args) throws FileNotFoundException, IOException {
        // TODO code application logic here
        BufferedReader readFile = new BufferedReader(new FileReader("input8.txt")); //GET NEXT FROM FILE
        String[] readLine = readFile.readLine().split(" ");
        int[] twoNumbers = new int[readLine.length]; //NEW TWO ITEM ARRAY
        for (int i = 0; i < readLine.length; i++) { //twoNum[0] height of matrix twoNum[1] width of matrix
            twoNumbers[i] = Integer.parseInt(readLine[i]); //Convert from string to int
            if (twoNumbers[i] < 1) {//Cant have a 0 or negative matrix
                System.out.println("Cannot Have Value less than 1. THANK YOU DINNOOOOO");
                System.exit(0);
            }
        }
        int n = (twoNumbers[0] - 1) + (twoNumbers[1] - 1); //WHEN DOING COMB N = (Height-1)+(Width-1)
        int r = twoNumbers[1] - 1; //THE AMOUND OF MOVES RIGHT IS WHAT MATTERS
        System.out.println(comb(n, r)); //CALC WITH N AND R
        //n = combinationCalculator((twoNumbers[0]-1),(twoNumbers[1]-1));
        //System.out.println(n);
    }

}
