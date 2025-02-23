/**
 * The Stock class represents a stock with a symbol, price, volume, and market capitalization.
 * It provides getters and setters to access and modify the stock's attributes.
 */
public class Stock {
    private String symbol;
    private double price;
    private long volume;
    private long marketCap;

    /**
     * Constructs a new Stock with the specified symbol, price, volume, and market capitalization.
     * @param symbol the stock symbol
     * @param price the stock price
     * @param volume the trading volume
     * @param marketCap the market capitalization
     */
    public Stock(String symbol, double price, long volume, long marketCap) {
        this.symbol = symbol;
        this.price = price;
        this.volume = volume;
        this.marketCap = marketCap;
    }

    /**
     * Gets the stock symbol.
     * @return the stock symbol
     */
    public String getSymbol() {
        return symbol;
    }

    /**
     * Sets the stock symbol.
     * @param symbol the new stock symbol
     */
    public void setSymbol(String symbol) {
        this.symbol = symbol;
    }

    /**
     * Gets the stock price.
     * @return the stock price
     */
    public double getPrice() {
        return price;
    }

    /**
     * Sets the stock price.
     * @param price the new stock price
     */
    public void setPrice(double price) {
        this.price = price;
    }

    /**
     * Gets the trading volume.
     * @return the trading volume
     */
    public long getVolume() {
        return volume;
    }

    /**
     * Sets the trading volume.
     * @param volume the new trading volume
     */
    public void setVolume(long volume) {
        this.volume = volume;
    }

    /**
     * Gets the market capitalization.
     * @return the market capitalization
     */
    public long getMarketCap() {
        return marketCap;
    }

    /**
     * Sets the market capitalization.
     * @param marketCap the new market capitalization
     */
    public void setMarketCap(long marketCap) {
        this.marketCap = marketCap;
    }

    /**
     * Returns a string representation of the Stock.
     * @return a string representation of the Stock
     */
    @Override
    public String toString() {
        return "Stock [symbol=" + symbol + ", price=" + price + ", volume=" + volume + ", marketCap=" + marketCap + "]";
    }
}
