/**
 * The StockDataManager class manages a collection of stocks using an AVL tree for efficient storage and retrieval.
 * It provides methods to add, update, remove, and search for stocks, as well as to print the stock data in various orders.
 */
public class StockDataManager {
    private AVLTree avlTree;

    /**
     * Constructs a new StockDataManager and initializes the AVL tree.
     */
    public StockDataManager() {
        avlTree = new AVLTree();
    }

    /**
     * Adds a new stock or updates an existing stock with the provided details.
     * @param symbol the stock symbol
     * @param price the stock price
     * @param volume the trading volume
     * @param marketCap the market capitalization
     */
    public void addOrUpdateStock(String symbol, double price, long volume, long marketCap) {
        Stock existingStock = avlTree.search(symbol);
        if (existingStock != null) {
            existingStock.setPrice(price);
            existingStock.setVolume(volume);
            existingStock.setMarketCap(marketCap);
        } else {
            Stock newStock = new Stock(symbol, price, volume, marketCap);
            avlTree.insert(newStock);
        }
    }

    /**
     * Removes a stock with the specified symbol.
     * @param symbol the stock symbol to remove
     */
    public void removeStock(String symbol) {
        avlTree.delete(symbol);
    }

    /**
     * Searches for a stock with the specified symbol.
     * @param symbol the stock symbol to search for
     * @return the Stock object if found, or null if not found
     */
    public Stock searchStock(String symbol) {
        return avlTree.search(symbol);
    }

    /**
     * Updates the details of an existing stock and re-inserts it into the AVL tree.
     * @param symbol the current stock symbol
     * @param newSymbol the new stock symbol
     * @param newPrice the new stock price
     * @param newVolume the new trading volume
     * @param newMarketCap the new market capitalization
     */
    public void updateStock(String symbol, String newSymbol, double newPrice, long newVolume, long newMarketCap) {
        Stock stock = avlTree.search(symbol);

        if (stock != null) {
            stock.setSymbol(newSymbol);
            stock.setPrice(newPrice);
            stock.setVolume(newVolume);
            stock.setMarketCap(newMarketCap);
            removeStock(symbol);
            avlTree.insert(stock); // Re-insert the updated stock
        }
    }

    /**
     * Prints the stock data in in-order traversal of the AVL tree.
     */
    public void printInOrder() {
        avlTree.inOrderTraversal();
    }

    /**
     * Prints the stock data in pre-order traversal of the AVL tree.
     */
    public void printPreOrder() {
        avlTree.preOrderTraversal();
    }

    /**
     * Prints the stock data in post-order traversal of the AVL tree.
     */
    public void printPostOrder() {
        avlTree.postOrderTraversal();
    }

    /**
     * Main method for testing the StockDataManager class.
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        StockDataManager manager = new StockDataManager();
        manager.addOrUpdateStock("AAPL", 150.0, 1000000, 2500000000L);
        manager.addOrUpdateStock("GOOGL", 2800.0, 500000, 1500000000L);
        System.out.println(manager.searchStock("AAPL"));
        manager.removeStock("AAPL");
        System.out.println(manager.searchStock("AAPL"));
    }
}
