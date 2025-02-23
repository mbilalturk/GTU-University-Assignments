import java.util.Arrays;

public class SelectionSort extends SortAlgorithm {

	public SelectionSort(int input_array[]) {
		super(input_array);
	}

    @Override
    public void sort() {
        // for loop to iterate all element
        for(int i=0; i<arr.length-1; ++i) {
            // initialize minIndex with i
            int minIndex = i;

            // for loop to iterate elements at indexes greater than i
            for(int j = i + 1; j < arr.length; ++j) {
                // if current element is less than element at minIndex, change minIndex to current index
                if(arr[j] < arr[minIndex])
                    minIndex = j;
                comparison_counter += 1;
            }

            // swap elements at i and minIndex
            swap(i, minIndex);
        }
    }

    @Override
    public void print() {
    	System.out.print("Selection Sort\t=>\t");
    	super.print();
    }
}
