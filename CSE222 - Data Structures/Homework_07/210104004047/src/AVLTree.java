/**
 * The AVLTree class represents a balanced binary search tree (AVL tree)
 * for storing Stock objects. It provides methods for insertion, deletion,
 * searching, and traversals (in-order, pre-order, post-order).
 */
public class AVLTree {
    private class Node {
        Stock stock;
        Node left, right;
        int height;

        /**
         * Constructs a new Node with the given stock.
         * @param stock the stock to be stored in the node
         */
        Node(Stock stock) {
            this.stock = stock;
            this.height = 1;
        }
    }

    private Node root;

    /**
     * Inserts a new stock into the AVL tree.
     * @param stock the stock to insert
     */
    public void insert(Stock stock) {
        root = insert(root, stock);
    }

    /**
     * Helper method to insert a new stock into the AVL tree recursively.
     * @param node the current node
     * @param stock the stock to insert
     * @return the updated node
     */
    private Node insert(Node node, Stock stock) {
        // Base case: found the correct position to insert the new node
        if(node == null)
            return new Node(stock);

        // Avoid duplicate keys
        if(node.stock.getSymbol().equals(stock.getSymbol()))
            return node;

        // Recursive insertion in the left or right subtree
        else if(node.stock.getSymbol().compareTo(stock.getSymbol()) > 0) {
            node.left = insert(node.left, stock);
        }
        else {
            node.right = insert(node.right, stock);
        }

        // Update the height of the current node
        updateHeight(node);

        // Calculate the balance factor
        int bf = calculateBalanceFactor(node);

        // Left-Left case
        if(bf > 1 && (node.left.stock.getSymbol().compareTo(stock.getSymbol()) > 0))
            return rotateRight(node);

        // Right-Right case
        if(bf < -1 && (node.right.stock.getSymbol().compareTo(stock.getSymbol()) < 0))
            return rotateLeft(node);

        // Left-Right case
        if(bf > 1 && (node.left.stock.getSymbol().compareTo(stock.getSymbol()) < 0)) {
            return rotateLeftRight(node);
        }

        // Right-Left case
        if(bf < -1 && (node.right.stock.getSymbol().compareTo(stock.getSymbol()) > 0)) {
            return rotateRightLeft(node);
        }

        return node;
    }

    /**
     * Deletes a stock with the given symbol from the AVL tree.
     * @param symbol the stock symbol to delete
     */
    public void delete(String symbol) {
        root = delete(root, symbol);
    }

    /**
     * Helper method to delete a stock from the AVL tree recursively.
     * @param node the current node
     * @param symbol the stock symbol to delete
     * @return the updated node
     */
    private Node delete(Node node, String symbol) {
        // Base case: node not found
        if (node == null)
            return null;

        // Recursive search for the node to delete
        if (node.stock.getSymbol().compareTo(symbol) < 0) {
            node.right = delete(node.right, symbol);
        }
        else if (node.stock.getSymbol().compareTo(symbol) > 0) {
            node.left = delete(node.left, symbol);
        }
        else {
            // Node found
            if(node.left == null) {
                node = node.right;
                return node;
            }
            else if(node.right == null) {
                node = node.left;
                return node;
            }
            else {
                // Node with two children: get the inorder successor (smallest in the right subtree)
                Node temp = getMinumumNode(node.right);
                // Copy the inorder successor's data to this node
                assert temp != null;
                node.stock = temp.stock;
                // Delete the inorder successor
                node.right = delete(node.right, temp.stock.getSymbol());
            }
        }

        // Update the height of the current node
        updateHeight(node);

        // Calculate the balance factor
        int bf = calculateBalanceFactor(node);

        // Left-Left case
        if(bf > 1 && (calculateBalanceFactor(node.left) >= 0))
            return rotateRight(node);

        // Right-Right case
        if(bf < -1 && (calculateBalanceFactor(node.right) <= 0))
            return rotateLeft(node);

        // Left-Right case
        if(bf > 1 && (calculateBalanceFactor(node.left) < 0)) {
            return rotateLeftRight(node);
        }

        // Right-Left case
        if(bf < -1 && (calculateBalanceFactor(node.right) > 0)) {
            return rotateRightLeft(node);
        }

        return node;
    }

    /**
     * Helper method to find the node with the minimum value in the subtree.
     * @param node the root of the subtree
     * @return the node with the minimum value
     */
    private Node getMinumumNode(Node node) {
        if(node == null)
            return null;

        if(node.left == null)
            return node;

        return getMinumumNode(node.left);
    }

    /**
     * Searches for a stock with the given symbol in the AVL tree.
     * @param symbol the stock symbol to search for
     * @return the Stock object if found, or null if not found
     */
    public Stock search(String symbol) {
        Node result = search(root, symbol);
        return (result != null) ? result.stock : null;
    }

    /**
     * Helper method to search for a stock in the AVL tree recursively.
     * @param node the current node
     * @param symbol the stock symbol to search for
     * @return the node containing the stock, or null if not found
     */
    private Node search(Node node, String symbol) {
        // Base case: node is null
        if(node == null)
            return null;

        // Compare the current node's symbol with the target symbol
        if(node.stock.getSymbol().compareTo(symbol) < 0) {
            // Target symbol is greater, search in the right subtree
            return search(node.right, symbol);
        }
        else if(node.stock.getSymbol().compareTo(symbol) > 0) {
            // Target symbol is smaller, search in the left subtree
            return search(node.left, symbol);
        }

        // Target symbol matches the current node's symbol
        return node;
    }

    /**
     * Performs a right rotation on the given node.
     * @param node the node to rotate
     * @return the new root after rotation
     */
    private Node rotateRight(Node node) {
        if (node != null && node.left != null) {
            Node newRoot = node.left;
            node.left = newRoot.right;
            newRoot.right = node;

            updateHeight(node);
            updateHeight(newRoot);

            return newRoot;
        }
        return node;
    }

    /**
     * Performs a left rotation on the given node.
     * @param node the node to rotate
     * @return the new root after rotation
     */
    private Node rotateLeft(Node node) {
        if (node != null && node.right != null) {
            Node newRoot = node.right;
            node.right = newRoot.left;
            newRoot.left = node;

            updateHeight(node);
            updateHeight(newRoot);

            return newRoot;
        }
        return node;
    }

    /**
     * Performs a right-left rotation on the given node.
     * @param node the node to rotate
     * @return the new root after rotation
     */
    private Node rotateRightLeft(Node node) {
        if (node != null && node.right != null) {
            node.right = rotateRight(node.right);
            return rotateLeft(node);
        }
        return node;
    }

    /**
     * Performs a left-right rotation on the given node.
     * @param node the node to rotate
     * @return the new root after rotation
     */
    private Node rotateLeftRight(Node node) {
        if (node != null && node.left != null) {
            node.left = rotateLeft(node.left);
            return rotateRight(node);
        }
        return node;
    }

    /**
     * Updates the height of the given node.
     * @param node the node to update
     */
    private void updateHeight(Node node) {
        if(node != null) {
            int leftHeight = (node.left != null) ? node.left.height : 0;
            int rightHeight = (node.right != null) ? node.right.height : 0;
            node.height = 1 + Math.max(leftHeight, rightHeight);
        }
    }

    /**
     * Calculates the balance factor of the given node.
     * @param node the node to calculate
     * @return the balance factor of the node
     */
    private int calculateBalanceFactor(Node node) {
        if(node == null)
            return 0;

        int leftHeight = (node.left != null) ? node.left.height : 0;
        int rightHeight = (node.right != null) ? node.right.height : 0;

        return leftHeight - rightHeight;
    }

    /**
     * Performs an in-order traversal of the AVL tree and prints the stock data.
     */
    public void inOrderTraversal() {
        inOrderTraversal(root);
    }

    /**
     * Helper method to perform an in-order traversal of the AVL tree recursively.
     * @param node the current node
     */
    private void inOrderTraversal(Node node) {
        if (node != null) {
            inOrderTraversal(node.left);
            System.out.println(node.stock);
            inOrderTraversal(node.right);
        }
    }

    /**
     * Performs a pre-order traversal of the AVL tree and prints the stock data.
     */
    public void preOrderTraversal() {
        preOrderTraversal(root);
    }

    /**
     * Helper method to perform a pre-order traversal of the AVL tree recursively.
     * @param node the current node
     */
    private void preOrderTraversal(Node node) {
        if (node != null) {
            System.out.println(node.stock);
            preOrderTraversal(node.left);
            preOrderTraversal(node.right);
        }
    }

    /**
     * Performs a post-order traversal of the AVL tree and prints the stock data.
     */
    public void postOrderTraversal() {
        postOrderTraversal(root);
    }

    /**
     * Helper method to perform a post-order traversal of the AVL tree recursively.
     * @param node the current node
     */
    private void postOrderTraversal(Node node) {
        if (node != null) {
            postOrderTraversal(node.left);
            postOrderTraversal(node.right);
            System.out.println(node.stock);
        }
    }
}
