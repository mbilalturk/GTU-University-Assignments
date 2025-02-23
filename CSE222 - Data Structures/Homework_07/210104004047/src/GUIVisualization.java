import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

/**
 * The GUIVisualization class represents a JFrame for visualizing performance graphs
 * based on provided data points. It supports line and scatter plots.
 */
public class GUIVisualization extends JFrame {
    private List<Long> dataPointsX;
    private List<Long> dataPointsY;
    private String plotType;

    /**
     * Constructs a GUIVisualization object with the specified plot type, data points, size, and title.
     * @param plotType the type of plot ("line" or "scatter")
     * @param dataPointsY the list of data points for the y-axis
     * @param size the size of the data points
     * @param title the title of the visualization window
     */
    public GUIVisualization(String plotType, List<Long> dataPointsY, int size, String title) {
        this.plotType = plotType;
        this.dataPointsX = new ArrayList<>();
        this.dataPointsY = dataPointsY;

        for (int i = 1; i <= size; i++) {
            dataPointsX.add((long) (i * 100));
        }

        setTitle("Performance Graph Visualization - " + title);
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    /**
     * Overrides the paint method to draw the graph on the JFrame.
     * @param g the Graphics object
     */
    @Override
    public void paint(Graphics g) {
        super.paint(g);
        drawGraph(g);
    }

    /**
     * Draws the graph on the specified Graphics object.
     * @param g the Graphics object
     */
    private void drawGraph(Graphics g) {
        int width = getWidth();
        int height = getHeight();
        int padding = 50;
        int labelPadding = 20;

        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        g2.setColor(Color.WHITE);
        g2.fillRect(padding + labelPadding, padding, width - 2 * padding - labelPadding, height - 2 * padding - labelPadding);
        g2.setColor(Color.BLACK);

        // Draw y axis and labels
        int numberYDivisions = 10;
        for (int i = 0; i < numberYDivisions + 1; i++) {
            int x0 = padding + labelPadding;
            int x1 = width - padding;
            int y0 = height - ((i * (height - padding * 2 - labelPadding)) / numberYDivisions + padding);
            int y1 = y0;
            if (dataPointsY.size() > 0) {
                g2.setColor(Color.LIGHT_GRAY);
                g2.drawLine(padding + labelPadding + 1 + labelPadding, y0, x1, y1);
                g2.setColor(Color.BLACK);
                double logScaleY = Math.pow(10, (i * (Math.log10(getMaxYValue()) / numberYDivisions)));
                String yLabel = String.format("%.1f", logScaleY);
                FontMetrics metrics = g2.getFontMetrics();
                int labelWidth = metrics.stringWidth(yLabel);
                g2.drawString(yLabel, x0 - labelWidth - 5, y0 + (metrics.getHeight() / 2) - 3);
            }
        }

        // Draw x axis and labels
        for (int i = 0; i < dataPointsX.size(); i++) {
            if (dataPointsX.size() > 1) {
                int x0 = i * (width - padding * 2 - labelPadding) / (dataPointsX.size() - 1) + padding + labelPadding;
                int x1 = x0;
                int y0 = height - padding - labelPadding;
                int y1 = y0 - 4;
                if ((i % ((int) ((dataPointsX.size() / 20.0)) + 1)) == 0) {
                    g2.setColor(Color.LIGHT_GRAY);
                    g2.drawLine(x0, height - padding - labelPadding - 1 - labelPadding, x1, padding);
                    g2.setColor(Color.BLACK);
                    String xLabel = dataPointsX.get(i) + "";
                    FontMetrics metrics = g2.getFontMetrics();
                    int labelWidth = metrics.stringWidth(xLabel);
                    g2.drawString(xLabel, x0 - labelWidth / 2, y0 + metrics.getHeight() + 3);
                }
                g2.drawLine(x0, y0, x1, y1);
            }
        }

        // Draw axes
        g2.drawLine(padding + labelPadding, height - padding - labelPadding, padding + labelPadding, padding);
        g2.drawLine(padding + labelPadding, height - padding - labelPadding, width - padding, height - padding - labelPadding);

        // Plot data
        Stroke oldStroke = g2.getStroke();
        g2.setColor(Color.BLUE);
        g2.setStroke(new BasicStroke(2f));

        if (plotType.equals("line")) {
            for (int i = 0; i < dataPointsX.size() - 1; i++) {
                int x1 = i * (width - padding * 2 - labelPadding) / (dataPointsX.size() - 1) + padding + labelPadding;
                int y1 = height - padding - labelPadding - (int) ((Math.log10(dataPointsY.get(i)) * 1.0) / getMaxLogYValue() * (height - padding * 2 - labelPadding));
                int x2 = (i + 1) * (width - padding * 2 - labelPadding) / (dataPointsX.size() - 1) + padding + labelPadding;
                int y2 = height - padding - labelPadding - (int) ((Math.log10(dataPointsY.get(i + 1)) * 1.0) / getMaxLogYValue() * (height - padding * 2 - labelPadding));
                g2.drawLine(x1, y1, x2, y2);
            }
        } else if (plotType.equals("scatter")) {
            for (int i = 0; i < dataPointsX.size(); i++) {
                int x = i * (width - padding * 2 - labelPadding) / (dataPointsX.size() - 1) + padding + labelPadding;
                int y = height - padding - labelPadding - (int) ((Math.log10(dataPointsY.get(i)) * 1.0) / getMaxLogYValue() * (height - padding * 2 - labelPadding));
                g2.fillOval(x - 3, y - 3, 6, 6);
            }
        }

        g2.setStroke(oldStroke);
    }

    /**
     * Calculates the maximum log value of the data points on the y-axis.
     * @return the maximum log value
     */
    private double getMaxLogYValue() {
        double max = Double.MIN_VALUE;
        for (Long y : dataPointsY) {
            double logY = Math.log10(y);
            max = Math.max(max, logY);
        }
        return max;
    }

    /**
     * Calculates the maximum value of the data points on the y-axis.
     * @return the maximum Y value
     */
    private long getMaxYValue() {
        long max = Long.MIN_VALUE;
        for (Long y : dataPointsY) {
            max = Math.max(max, y);
        }
        return max;
    }

    /*
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            ArrayList<Long> times = new ArrayList<>(5);
            times.add(500L);
            times.add(500L);
            times.add(6000L);
            times.add(8000L);
            times.add(40000L);

            String plotType = "line";
            GUIVisualization frame = new GUIVisualization(plotType, times, times.size(), "Add");

            frame.setVisible(true);
        });
    }
    */
}
