/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package project6comp482;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import static java.time.temporal.TemporalAdjusters.previous;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

/**
 *
 * @author yups
 */
public class Project6COMP482 {

    public static void calculateList(int index, int sum, List<Integer> temp, List<List<Integer>> ret) {
        int[] nums = {1, 2}; //POSSIBLE OPTIONS
        if (sum == 0) { //MAX STAIRS HAS BEEN HIT
            ret.add(new ArrayList<>(temp)); //ADD NEW ARRAYLIST CONTAINING TEMP
            permutationSet(temp); //SEND LIST TO PERMUTATIONS
        }
        for (int i = index; i < nums.length && nums[i] <= sum; i++) {
            temp.add(nums[i]); //ADD VALUE OF nums[I] TO TEMP
            calculateList(i, sum - nums[i], temp, ret);//RECURSIVLY CALL CALCULATE LIST
            temp.remove(temp.size() - 1);//REMOVE OBJECT
        }
    }

    public static void permutationSet(List<Integer> tempList) {//DID SETS CAUSE NO DUPLICATES
        ArrayList<ArrayList<Integer>> returnList = new ArrayList<ArrayList<Integer>>();//LIST TO SOUT END
        returnList.add(new ArrayList<Integer>());//ADD Object
        for (int i = 0; i < tempList.size(); i++) {//GO THROUGH HOW MANY OF PASSED SET AMOUNT
            Set<ArrayList<Integer>> currentSet = new HashSet<ArrayList<Integer>>();//CREATE SET
            for (List<Integer> l : returnList) {//GO THROUGH RETURN LIST
                for (int j = 0; j < l.size() + 1; j++) {//GO THROUGH EACH LIST
                    l.add(j, tempList.get(i));//ADD TEMPLIST ITEM TO INDEX J
                    ArrayList<Integer> T = new ArrayList<Integer>(l); //NEW ARRAYLIST WITH L VALUE
                    l.remove(j);//REMOVE J FROM L
                    currentSet.add(T);
                }
            }
            returnList = new ArrayList<ArrayList<Integer>>(currentSet);//LIST WITH CURRENT SET
        }
        for (ArrayList<Integer> list : returnList) { //GO THROUGH RETURN LIST
            System.out.print("Starting from step 0 go up ");
            String joinedString;
            joinedString = list.stream().map(n -> n.toString()).collect(Collectors.joining("+"));//COMBINE STRINGS WITH + DELIMITER
            System.out.print(joinedString + "\n");
            
        }
    }

    public static void main(String[] args) throws Exception {
        BufferedReader readFile = new BufferedReader(new FileReader("input6.txt"));//READ FILE
        int maxStairs = Integer.parseInt(readFile.readLine());//CONVERT TO INT
        //System.out.println(maxStairs);
        List<List<Integer>> returned = new ArrayList();
        calculateList(0,maxStairs,new ArrayList(), returned);
    }

}
