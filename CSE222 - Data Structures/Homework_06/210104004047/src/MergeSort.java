public class MergeSort extends SortAlgorithm {
	
	public MergeSort(int input_array[]) {
		super(input_array);
	}

    private void merge(int lowest, int middle, int highest) {

        // Determine the size of left array and right array
        int n1 = middle - lowest + 1;
        int n2 = highest - middle;

        // Create left array and right array
        int[] leftArray = new int[n1];
        int[] rightArray = new int[n2];

        // Initialize leftArray
        for (int i = 0; i < n1; ++i)
            leftArray[i] = arr[lowest + i];

        // Initialize rightArray
        for (int j = 0; j < n2; ++j)
            rightArray[j] = arr[middle + 1 + j];

        int i = 0; // index for leftArray
        int j = 0; // index for rightArray
        int k = lowest;  // left-most index of array

        // If i and j is less than size left array and right array respectively
        while (i < n1 && j < n2) {
            comparison_counter++;

            // If element at leftArray is less than element at rightArray, fill arr with element at leftArray then increment i.
            // Otherwise, fill arr with element at rightArray then increment j.
            if (leftArray[i] <= rightArray[j]) {
                arr[k] = leftArray[i];
                i++;
            } else {
                arr[k] = rightArray[j];
                j++;
            }
            k++;
        }

        // Copy remaining elements of leftArray, if any.
        while (i < n1) {
            arr[k] = leftArray[i];
            i++;
            k++;
        }

        // Copy remaining elements of rightArray, if any.
        while (j < n2) {
            arr[k] = rightArray[j];
            j++;
            k++;
        }
    }


    private void sort(int lowest, int highest){
        // If lowest is less than highest, which means there are at least two element
        if(lowest < highest) {
            // Determine middle index of array
            int middle = (lowest + highest) / 2;

            // call sort method for left of pivot
            sort(lowest, middle);

            // call sort method for right of pivot
            sort(middle+ 1, highest);

            // call merge method
            merge(lowest, middle, highest);
        }

    }

    
    @Override
    public void sort() {
        // 4, 2, 6, 5, 1, 8, 7, 3
    	sort(0, arr.length - 1);
    }
    
    @Override
    public void print() {
    	System.out.print("Merge Sort\t=>\t");
    	super.print();
    }
}
