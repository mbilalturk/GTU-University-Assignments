public class BubbleSort extends SortAlgorithm {

	public BubbleSort(int input_array[]) {
		super(input_array);
	}

    @Override
    public void sort() {
        // for loop to iterate all element
        for(int i=0; i<arr.length; ++i) {
            // flag to check if swapping is applied
            boolean swapped = false;

            for(int j = 0; j < arr.length - i - 1; ++j) {
                // If fallowing element less than current element, swap them
                if(arr[j + 1] < arr[j]) {
                    swap(j, j + 1);
                    swapped = true;
                }
                comparison_counter += 1;
            }

            // If swapped is false which means array is sorted, break
            if(!swapped)
                break;
        }
    }
    
    @Override
    public void print() {
    	System.out.print("Bubble Sort\t=>\t");
    	super.print();
    }
}
