import java.util.Random;
public class createRandomNum{
    public static void main(String [] args){
        int [] arr = new int [1000000];
        Random random = new Random();
        for (int i = 0; i < arr.length; i++) {
            arr[i] = random.nextInt(1000000) + 1; // random number between 1 and ...
        }
        arr[arr.length/4] = (-1)*arr[arr.length/4];
        arr[arr.length/2] = (-1)*arr[arr.length/2];
        arr[3*(arr.length/4)] = (-1)*arr[3*(arr.length/4)];
        for (int i = 0; i < arr.length; i++) {
            System.out.println(arr[i]);
        }
        // System.out.println(arr[arr.length/4]);
        // System.out.println(arr[arr.length/2]);
        // System.out.println(arr[3*(arr.length/4)]);
        
    }
}