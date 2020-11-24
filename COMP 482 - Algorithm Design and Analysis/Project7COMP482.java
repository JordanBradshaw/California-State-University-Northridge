/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package project7comp482;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author yups
 */
public class Project7COMP482 {

    public static void main(String[] args) throws FileNotFoundException, IOException {
        BufferedReader readFile = new BufferedReader(new FileReader("input7.txt")); //ET FILE
        String[] stringArray = readFile.readLine().split(" ");// DELIM SPACES
        int[] intArray = new int[stringArray.length];// CREATE INT ARRAY
        for (int i = 0; i < stringArray.length; i++) {//CONVERT FROM STRING TO INT
            intArray[i] = Integer.parseInt(stringArray[i]);
        }
        int HighestCombination = intArray[0];//START WITH VALUE CONTAINED IN ARRAY SLOT 0
        for (int i = 0; i < intArray.length; i++) {//GO LEFT TO RIGHT ON ARRAY
            if (intArray[i] > HighestCombination) {//IF VALUE CONTAINED IS HIGHER THAN CURRENT HIGHEST
                HighestCombination = intArray[i];//SET HIGHEST TO NEW VALUE
            }
            if (i == intArray.length - 1) { //IF INDEX IS AT END OF ARRAY THEN SUCCESS
                System.out.println("Success");
            } else if (HighestCombination == 0) { //IF SPACES RUNS INTO 0 MOVES AND NOT AT END OF ARRAY
                System.out.println("Fail");
                return;
            }
            HighestCombination--; //EACH STEP WE GO UP SO AMOUNT OF STEPS THAT WE CAN MOVE GOES DOWN
        }
    }
}
