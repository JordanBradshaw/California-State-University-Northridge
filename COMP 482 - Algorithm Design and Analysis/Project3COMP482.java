/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package project3comp482;

import java.io.BufferedReader;
import java.io.FileReader;

/**
 *
 * @author yups
 */
public class Project3COMP482 {

    static int[] numberArray;
    //static int[] tempArray;
    static int counter = 0;

    /**
     * @param args the command line arguments
     */
    /*public static int calculateHalfArray(int[] passedArray) {
        int arrayHalfSize;
        int arrayTotalSize = passedArray.length - 1;
        if (arrayTotalSize % 2 == 0) {
            arrayHalfSize = (arrayTotalSize / 2);
        } else {
            arrayHalfSize = (arrayTotalSize / 2);
        }
        return arrayHalfSize - 1;
    }*/

    public static void merge(int[] passedArray, int left, int middle, int right) {
        //int i = left, j = middle + 1, k = left;
        //int index1 = middle - left + 1;
        //int index2 = right - middle;
        int[] leftArray = new int[middle - left + 1]; //DECLARING ARRAY AND SIZE
        int[] rightArray = new int[right - middle];//DECLARING ARRAY AND SIZE
        for (int m = 0; m < leftArray.length; m++) {//LOAD TEMP LEFT ARRAY
            leftArray[m] = passedArray[left + m];
        }
        for (int n = 0; n < rightArray.length; n++) {//LOAD TEMP RIGHT ARRAY
            rightArray[n] = passedArray[middle + 1 + n];
        }
        int leftIndex = 0;//INDEX VARIABLE FOR LEFT
        int rightIndex = 0;//INDEX VARIABLE FOR RIGHT
        for (int j = left; j < right + 1; j++) {//DO A FULL LEFT TO RIGHT OF ARRAY
            if ((leftIndex < leftArray.length) && (rightIndex < rightArray.length)) {
                if (leftArray[leftIndex] <= rightArray[rightIndex]) {//IF LEFT ARRAY IS LESS THAN RIGHT ARRAY
                    passedArray[j] = leftArray[leftIndex];//PLACE INT IN LEFT INTO MAIN ARRAY
                    counter += (j - (left + leftIndex));//CALCULATE DIFFERENCE FROM ORIGINAL POSITION
                    leftIndex++;
                    //counter++;
                } else {
                    passedArray[j] = rightArray[rightIndex];//ELSE PLACE INT IN RIGHT ARRAY
                    //counter += ((right + rightIndex) - j);
                    rightIndex++;
                }
            } else if (leftIndex < leftArray.length) {//FILL WITH REST OF ARRAY IF DONE WITH RIGHT
                passedArray[j] = leftArray[leftIndex];
                counter += (j - (left + leftIndex));//CALCULATE DISPLACEMENT
                leftIndex++;
            } else if (rightIndex < rightArray.length) {//FILL WITH REST OF RIGHT ARRAY IF LEFT IS DONE
                passedArray[j] = rightArray[rightIndex];
                rightIndex++;
                //counter++;
            }
        }
    }

    /*public static void mergeSortInit(int[] passedArray) {
        numberArray = passedArray;
        tempArray = new int[numberArray.length];
    }
     */
    public static void mergeSort(int[] passedArray, int mergeLeft, int mergeRight) {
        if (mergeRight <= mergeLeft) {
            return;
        }
        int middle = (mergeLeft + mergeRight) / 2;
        mergeSort(passedArray, mergeLeft, middle);//Mergesort left half
        mergeSort(passedArray, (middle + 1), mergeRight);//Mergesort right half
        merge(passedArray, mergeLeft, middle, mergeRight);//Mergesort all

        //}
    }

    public static void main(String[] args) {
        String line;
        String[] lineArray;
        int[] passArray;
        try {//READER FOR THE FILE
            BufferedReader reader = new BufferedReader(new FileReader("input3.txt"));
            line = reader.readLine();
            lineArray = line.split(" ");//MAKE INTO AN ARRAY
            passArray = new int[lineArray.length];
            for (int i = 0; i < lineArray.length; i++) {//convert ftom string to int
                passArray[i] = Integer.parseInt(lineArray[i]);
            }
            //mergeSortInit(passArray);
            mergeSort(passArray, 0, passArray.length - 1);
        } catch (Exception e) {
            System.out.println(e.toString());
        }

        System.out.println(counter);
    }

}
