package app;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import lib.EditDist;
import java.util.Scanner;


public class AppMain {

  static String dictionaryPath = "data/dictionary.txt";
  static String correctmePath = "data/correctme.txt";

  public static ArrayList<String> loadDictionary(String path) throws Exception {
    BufferedReader br = new BufferedReader(new FileReader(path));
    String st;
    ArrayList<String> ret = new ArrayList<String>();
    while ((st = br.readLine()) != null)
      ret.add(st);

    return ret;
  }

  public static String loadFile(String path) throws Exception {
    BufferedReader br = new BufferedReader(new FileReader(path));
    String st, ret = "";
    while ((st = br.readLine()) != null)
      ret += st;
    return ret;
  }

  public static ArrayList<ArrayList<String>> calculateDistance(ArrayList<String> dict, String[] words) {
    ArrayList<ArrayList<String>> ret = new ArrayList<ArrayList<String>>();
    for (int i = 0; i < words.length; i++) {
      int min = Integer.MAX_VALUE;
      ArrayList<String> list = new ArrayList<String>();

      for (int j = 0; j < dict.size(); j++) {

        int distance = EditDist.edit_distance_dyn(words[i], dict.get(j));
        if (distance < min) {
          list.clear();
          list.add(dict.get(j));
          min = distance;
        } 
        else if (distance == min) {
          list.add(dict.get(j));
        }
      }
      ret.add(list);
    }
    return ret;
  }

  public static void printResult(ArrayList<ArrayList<String>> data, String[] words, boolean skipEquals) {
    int dist;
    for (int i = 0; i < data.size(); i++) {
      ArrayList<String> subArray = data.get(i);
      
      dist = EditDist.edit_distance_dyn(words[i], subArray.get(0));
      if (skipEquals && dist == 0)
        continue;

      System.out.print(words[i] + " has edit distance equal to " + dist + " from: ");

      for (int j = 0; j < data.get(i).size(); j++) {
        System.out.print(j == data.get(i).size() - 1 ? subArray.get(j) + "\n" : subArray.get(j) + ", ");
      }
    }
  }

  public static void main(String[] args) throws Exception {

    Boolean skipEquals = false;
    Scanner scan = new Scanner(System.in);
    long startTime, diffTime, executionTime;
    float elapsedTime;

    System.out.print("Do you want to print words even if distance == 0? [Y/n]:");
    skipEquals = scan.nextLine().toLowerCase().contains("y") ? false : true;

    startTime = System.currentTimeMillis();
    ArrayList<String> dict = loadDictionary(dictionaryPath);
    String[] words = loadFile(correctmePath).split("\\W+");
    diffTime = System.currentTimeMillis();
    elapsedTime = (diffTime - startTime) / (float) 1000;
    System.out.println("[OK] Data loaded successfully in " + elapsedTime + " seconds");

    executionTime = System.currentTimeMillis();
    ArrayList<ArrayList<String>> arrList = calculateDistance(dict, words);
    diffTime = System.currentTimeMillis();
    elapsedTime = (diffTime - executionTime) / (float) 1000;
    System.out.println("[OK] Calculation complete in " + elapsedTime + " seconds\n\n");

    printResult(arrList, words, skipEquals);

    diffTime = System.currentTimeMillis();
    elapsedTime = (diffTime - startTime) / (float) 1000;

    System.out.println("\n\n[OK]Total elapsed time: " + elapsedTime);

  }
}
