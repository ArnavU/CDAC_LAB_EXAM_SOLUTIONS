package com.sunbeam;

import java.util.Scanner;

public class Main {
	static Scanner sc = new Scanner(System.in);
	public static int menuList() {
		int choice;
		System.out.println("Enter your choice: ");
		System.out.println("0. END.");
		System.out.println("1. Insert a product.");
		System.out.println("2. Delete a product.");
		System.out.println("3. Display Products.");
		System.out.println("4. Search product by price.");
		System.out.println("5. Count expensive products.");
		System.out.println("6. Dislay products in given price range.");
		System.out.println("7. Find Kth Highest Product price.");
		choice = sc.nextInt();
		return choice;
	}

	public static void main(String[] args) {
		ProductBST bst = new ProductBST();
		
		bst.addNewProduct(1, "Soap", 100.50);
		bst.addNewProduct(2, "Keyboard", 200.50);
		bst.addNewProduct(3, "T-shirt", 90.50);
		bst.addNewProduct(4, "Shampoo", 10.50);
		bst.addNewProduct(5, "abc", 10.50);
//		
//		bst.displayBST();
//		bst.deleteProduct(200.50);
//		bst.deleteProduct(200.50);
//		bst.displayBST();
		
		int choice;
		while((choice = menuList()) > 0) {
			int id;
			String name;
			double price;
			double minPrice;
			double maxPrice;
			int k; 
			
			switch(choice) {
			case 1: // add new product
				System.out.print("Enter product id: ");
				id = sc.nextInt();
				System.out.print("Enter product name: ");
				name = sc.next();
				System.out.print("Enter product price: ");
				price = sc.nextDouble();
				bst.addNewProduct(id, name, price);
				break;
				
			case 2: // delete a product
				System.out.print("Enter the price to delete: ");
				price = sc.nextDouble();
				bst.deleteProduct(price);
				break;
			case 3: // display product prices in ascending order
				bst.displayBST();
				break;
			case 4: // search product by price
				System.out.print("Enter the search price: ");
				price = sc.nextDouble();
				bst.searchProduct(price);
				break;
			case 5: // count expensive products
				System.out.print("Enter expensive price threshold: ");
				price = sc.nextDouble();
				bst.displayExpensiveCount(price);
				break;
			case 6: // display in price range (inclusive)
				System.out.print("Enter min price: ");
				minPrice = sc.nextDouble();
				System.out.print("Enter max price: ");
				maxPrice = sc.nextDouble();
				bst.displayRange(minPrice, maxPrice);
				break;
			case 7: // kth highest product price
				System.out.print("Enter the value of k: ");
				k = sc.nextInt();
				bst.displayKthHighest(k);
				break;
			default: 
				System.out.println("Thank You. End of the program!!!");
			}
		}
		
	}

}






















