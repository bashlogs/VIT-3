    import java.util.Scanner;
    import java.util.Arrays;
    import java.util.*;
    public class cypher {
        public static void main(String[] args) {
            int[] p1 = {3,5,2,7,4,10,1,9,8,6};
            int[] p2 = {6,3,7,4,8,5,10,9};
            int[] key = {0,0,1,0,0,1,0,1,1,1};
            // int[] mod = new int[key.length];
            String mod = "";
            for(int i=0; i<key.length; i++){
                mod += key[p1[i]-1];
            }
            // int[] part1 = Arrays.copyOfRange(mod, 0, 5);
            // int[] part2 = Arrays.copyOfRange(mod, 5, 10);

            String part1 = mod.substring(0, 4);
            String part2 = mod.substring(4, 9);
            
            int int1 = Integer.parseInt(part1,2);
            int int2 = Integer.parseInt(part2,2);

            int shift1 = (int1 << 1) | (int1 >>> (part1.length() - 1));
            int shift2 = (int2 << 1) | (int2 >>> (part2.length() - 1));

            System.out.println(Integer.toBinaryString(shift1) + " " + Integer.toBinaryString(shift2));

                



        }
    }