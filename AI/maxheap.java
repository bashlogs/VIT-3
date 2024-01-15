public class maxheap {
    public static void heapify(int arr[], int len, int n){
        int root = len;
        int left = root*2+1;
        int right = root*2+2;

        if(left < n && arr[left] > arr[root]){
            root = left;
        }
        
        if(right < n && arr[right] > arr[root]){
            root = right;
        }

        if(root != len){
            int temp = arr[root];
            arr[root] = arr[len];
            arr[len] = temp;
        }
        
        if(len > 0){
            heapify(arr, len-1, n);
        }
    }

    public static void minheap1(int arr[], int n){
        int len = n/2-1;
        for(int i=n; i>0; i--){
            heapify(arr, len, i);
            int temp = arr[i-1];
            arr[i-1] = arr[0];
            arr[0] = temp;
        }
    }

    public static void main(String[] args) {
        int[] arr = {12, 13, 16, 5, 11, 2, 1};
        int n = arr.length;
        minheap1(arr, n);
        for(int i=0; i<n; i++){
            System.out.print(arr[i] + "\t");
        }
    }
}