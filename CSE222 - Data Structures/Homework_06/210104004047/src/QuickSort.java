public class QuickSort extends SortAlgorithm {

	public QuickSort(int input_array[]) {
		super(input_array);
	}

    private int partition(int lowestIndex, int highestIndex) {
        // Initialize pivot with last element of array
        int pivot = arr[highestIndex];

        // Initialize i with lowestIndex - 1
        int i = lowestIndex - 1;

        // for loop to iterate from lowestIndex to highestIndex
        for (int j = lowestIndex; j < highestIndex; j++) {
            comparison_counter++;

            // If current element is less than pivot, swap current element and element in i
            if (arr[j] < pivot) {
                i++;
                swap(i, j);
            }
        }

        // Swap elements at highestIndex and i + 1 which is correct position of pivot
        swap(i + 1, highestIndex);

        // return index of pivot
        return i + 1;
    }


    private void sort(int lowest, int highest){
        // If lowest is less than highest, which means there are at least two element
        if(lowest < highest) {
            // call partition method to determine position of pivot element
            int pivotIndex = partition(lowest, highest);

            // call sort method for left of pivot
            sort(lowest, pivotIndex - 1);

            // call sort method for right of pivot
            sort(pivotIndex + 1, highest);
        }
    }

    @Override
    public void sort() {
    	sort(0, arr.length - 1);
    }

    @Override
    public void print() {
    	System.out.print("Quick Sort\t=>\t");
    	super.print();
    }
}
