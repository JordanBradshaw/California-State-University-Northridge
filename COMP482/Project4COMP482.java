/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package project4comp482;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.IntStream;
import java.util.stream.Stream;

/**
 *
 * @author yups
 */
public class Project4COMP482 {

    static int capVar = 0;
    static Set<Item> finalSet;
    static int highestValue;

    public static class Item {

        private String name;
        private int value;
        private int weight;

        public Item(String passedName) {
            name = passedName;
            value = Integer.parseInt(name);
        }

        public void setWeight(String passedWeight) {
            weight = Integer.parseInt(passedWeight);
        }

        public int getValue() {
            return value;
        }

        public int getWeight() {
            return weight;
        }
    }

    public static <Item> Set<Item> convertArrayToSet(Item array[]) {
        Set<Item> set = new HashSet<>(); //CREATE EMPTY HASH SET
        for (Item t : array) { //GO THROUGH EVERY ITEM IN PASSED ARRAY
            set.add(t); //ADD EACH ELEMENT
        }
        return set; //RETURN CONVERTED SET
    }

    public static Set<Set<Item>> powerSet(Set<Item> tempItem) {//POWER SET ARRAY
        List<Item> S = new ArrayList<>(tempItem);
        long N = (long) Math.pow(2, S.size());
        Set<Set<Item>> result = new HashSet<>();
        for (int i = 1; i < N; i++) {
            Set<Item> set = new HashSet<>();
            for (int j = 0; j < S.size(); j++) {
                if ((i & (1 << j)) != 0) {
                    set.add(S.get(j));
                }
            }
            result.add(set);
        }
        result.remove(0);
        return result;
    }

    private static void calculateWeight(Set<Item> tempSet) {//STREAM WEIGHT OF ITEM
        Stream<Item> itemStream = tempSet.stream();
        int weightAdded = itemStream.mapToInt(x -> x.getWeight()).sum();
        if (weightAdded <= capVar) {
            calculateValue(tempSet);
            //System.out.println(weightAdded);
        }
        //System.out.println(weightAdded);
    }

    public static void calculateValue(Set<Item> tempSet) {//STREAM VALUES OF ITEM
        Stream<Item> itemStream = tempSet.stream();
        int valueAdded = itemStream.mapToInt(x -> x.getValue()).sum();
        if (valueAdded > highestValue){
            highestValue = valueAdded;
            finalSet = tempSet;
        } 
        //System.out.println(valueAdded);
    }

    public static void main(String[] args) {
        Item[] itemArray = null;
        String line;
        String[] lineArray;
        try {//READER FOR THE FILE
            BufferedReader readFile = new BufferedReader(new FileReader("input4.txt"));
            line = readFile.readLine();//FIRST LINE IS MAX WEIGHT
            capVar = Integer.parseInt(line); //CONVERT TO INT
            line = readFile.readLine(); //SECOND LINE IS VALUES
            lineArray = line.split(" ");//MAKE INTO AN ARRAY
            int numItems = lineArray.length;
            itemArray = new Item[numItems];
            for (int i = 0; i < numItems; i++) {//CONVERT VALUE STRINGS TO INT ARRAY
                itemArray[i] = new Item(lineArray[i]);
            }
            line = readFile.readLine();
            lineArray = line.split(" ");//MAKE INTO AN ARRAY
            for (int i = 0; i < numItems; i++) {//CONVERT WEIGHT STRINGS TO INT ARRAY
                itemArray[i].setWeight(lineArray[i]);
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
        Set<Item> setItem = convertArrayToSet(itemArray);
        Set<Set<Item>> powerItem = powerSet(setItem);
        powerItem.forEach(x -> calculateWeight(x));
        System.out.println(highestValue);
    }

}
