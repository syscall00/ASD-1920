package test;

import lib.EditDist;
import org.junit.*;

public class EditDistTest {

  @Test
  public void EditTestRec() {
    String s1 = "casa", s2 = "cassa";
    String s3 = "vinaio", s4 = "vino";
    String s5 = "pioppo";
    Assert.assertTrue(EditDist.edit_distance(s1, s2) == 1);
    Assert.assertTrue(EditDist.edit_distance(s3, s4) == 2);
    Assert.assertTrue(EditDist.edit_distance(s5, s5) == 0);
  }

  @Test
  public void EditTestRecEmpty() {
    String s1 = "";
    Assert.assertTrue(EditDist.edit_distance(s1, s1) == 0);
  }
  
  @Test
  public void EditTestDyn() {
    String s1 = "casa", s2 = "cassa";
    String s3 = "vinaio", s4 = "vino";
    String s5 = "pioppo";
    Assert.assertTrue(EditDist.edit_distance_dyn(s1, s2) == 1);
    Assert.assertTrue(EditDist.edit_distance_dyn(s3, s4) == 2);
    Assert.assertTrue(EditDist.edit_distance_dyn(s5, s5) == 0);
  }

  @Test
  public void EditTestDynEmpty() {
    String s1 = "";
    Assert.assertTrue(EditDist.edit_distance_dyn(s1, s1) == 0);
  }
}
