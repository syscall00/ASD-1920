package lib;

public class EditDist {

  /**
  * Get a string without his first char
  * @param s1   String to be manipulated  
  * @return     String without his first char
  */
  private static String rest(String s) {
    return s.length() > 0? s.substring(1,s.length()) : "";
  }
  
  /**
  * Calculates edit distance between two strings. Based on recurrency relationship given
  * @param s1    first string 
  * @param s2    second string
  * @return     edit distances between two strings
  */
  public static int edit_distance(String s1, String s2) {
    if (s1.length() == 0 || s2.length() == 0) {
      return s1.length() >= s2.length() ? s1.length() : s2.length();
    }
    else {

      int dNop = s1.charAt(0) == s2.charAt(0) ? edit_distance(rest(s1), rest(s2)) : Integer.MAX_VALUE;
      int dCanc = 1 + edit_distance(s1, rest(s2));
      int dIns = 1 + edit_distance(rest(s1), s2);

      return Math.min(Math.min(dNop, dCanc), dIns);
    }
  }

  /**
  * Calculates edit distance between two strings. Based on dynamic programming 
  * @param s1    first string 
  * @param s2    second string
  * @return     edit distances between two strings
  */
  public static int edit_distance_dyn(String s1, String s2) {int l1 = s1.length();
  int l2 = s2.length();

  int dyn[][] = new int[l1 + 1][l2 + 1];

  for (int i = 0; i <= l1; i++) {
    for (int j = 0; j <= l2; j++) {
      if (i == 0 || j == 0)
        dyn[i][j] = i >= j? i : j;
      
      else if (s1.charAt(i - 1) == s2.charAt(j - 1))
        dyn[i][j] = dyn[i - 1][j - 1];
      else
        dyn[i][j] = 1 + Math.min(dyn[i][j - 1], dyn[i - 1][j]);
      }
    }
    return dyn[l1][l2];
  }
}
