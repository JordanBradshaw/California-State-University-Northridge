/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package project5comp482;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author yups
 */
public class Project5COMP482 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            BufferedReader readFile = new BufferedReader(new FileReader("input5.txt"));//READ FILE
            String readLine = readFile.readLine();//GET STRING LINE
            String[] stringArray = readLine.split(" ");//BREAK INTO STRING ARRAY
            List<Integer> list = new ArrayList<Integer>();//NEW LIST
            for (String temp : stringArray) {//GO THROUGH ARRAY AND ADD THE ITEMS INTO LIST
                list.add(Integer.valueOf(temp));
            }
            list.stream()//CREATE STREAM
                    .sorted()//SORT SMALLEST TO LARGEST SO NEGATIVES ARE ON LEFT
                    .sorted((x, y) -> Integer.compare(Math.abs(x), Math.abs(y)))//SORT ABSOLUTE VALUE
                    .forEach(x -> System.out.print(x + " "));//PRINT
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }

}
