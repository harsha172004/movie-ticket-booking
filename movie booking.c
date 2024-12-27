#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store movie details
typedef struct {
    char name[50];
    int price;
    char theaterName[50];
    char location[50];
} Movie;

// Function to display the available movies with their details in a tabular format
void displayMovies(Movie movies[], int movieCount) {
    printf("\nAvailable Movies:\n");
    printf("--------------------------------------------------------------\n");
    printf("| %-4s | %-20s | %-6s | %-20s | %-15s |\n", "No.", "Movie Name", "Price", "Theater Name", "Location");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < movieCount; i++) {
        printf("| %-4d | %-20s | $%-5d | %-20s | %-15s |\n", 
               i + 1, movies[i].name, movies[i].price, movies[i].theaterName, movies[i].location);
    }
    printf("--------------------------------------------------------------\n");
}

// Function to book tickets
void bookTicket(Movie movies[], int movieChoice, int numTickets) {
    int price = movies[movieChoice].price;
    int totalCost = price * numTickets;

    printf("\nBooking Confirmation:\n");
    printf("--------------------------------------------------------------\n");
    printf("| %-20s | %-6s | %-20s | %-15s | %-10s |\n", "Movie Name", "Price", "Theater Name", "Location", "Tickets");
    printf("--------------------------------------------------------------\n");
    printf("| %-20s | $%-5d | %-20s | %-15s | %-10d |\n", 
           movies[movieChoice].name, movies[movieChoice].price, movies[movieChoice].theaterName, movies[movieChoice].location, numTickets);
    printf("--------------------------------------------------------------\n");
    printf("Total cost: $%d\n", totalCost);
}

// Function to cancel tickets
void cancelTicket(Movie movies[], int movieChoice, int numTickets) {
    printf("\nCancellation Confirmation:\n");
    printf("--------------------------------------------------------------\n");
    printf("| %-20s | %-6s | %-20s | %-15s | %-10s |\n", "Movie Name", "Price", "Theater Name", "Location", "Tickets");
    printf("--------------------------------------------------------------\n");
    printf("| %-20s | $%-5d | %-20s | %-15s | %-10d |\n", 
           movies[movieChoice].name, movies[movieChoice].price, movies[movieChoice].theaterName, movies[movieChoice].location, numTickets);
    printf("--------------------------------------------------------------\n");
}

int main() {
    // Array of movies with their names, but price, theater name, and location will be asked later
    Movie movies[] = {
        {"Movie 1", 0, "", ""},
        {"Movie 2", 0, "", ""},
        {"Movie 3", 0, "", ""},
        {"Movie 4", 0, "", ""}
    };
    int movieCount = sizeof(movies) / sizeof(movies[0]);
    int movieChoice, numTickets, option;
    int totalBookings = 0;

    printf("Welcome to the Movie Ticket Booking System!\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. View Total Bookings\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &option);

        if (option == 4) {
            printf("Exiting the system. Thank you for using the Movie Ticket Booking System!\n");
            break;
        }

        switch (option) {
            case 1:
                displayMovies(movies, movieCount);

                printf("\nEnter the movie number to book: ");
                scanf("%d", &movieChoice);
                movieChoice--; // Adjust for 0-based index

                if (movieChoice < 0 || movieChoice >= movieCount) {
                    printf("Invalid movie selection!\n");
                    break;
                }

                // Ask for the theater name, location, and price for the selected movie
                printf("Enter the theater name: ");
                getchar(); // To consume newline character left by previous input
                fgets(movies[movieChoice].theaterName, sizeof(movies[movieChoice].theaterName), stdin);
                movies[movieChoice].theaterName[strcspn(movies[movieChoice].theaterName, "\n")] = '\0'; // Remove newline character

                printf("Enter the location (e.g., Kadapa): ");
                fgets(movies[movieChoice].location, sizeof(movies[movieChoice].location), stdin);
                movies[movieChoice].location[strcspn(movies[movieChoice].location, "\n")] = '\0'; // Remove newline character

                // Ask for the price of the movie
                printf("Enter the price of the movie (e.g., 250): ");
                scanf("%d", &movies[movieChoice].price);

                // Ask for the number of tickets to book
                printf("Enter the number of tickets to book: ");
                scanf("%d", &numTickets);
                totalBookings += numTickets;

                bookTicket(movies, movieChoice, numTickets);
                break;

            case 2:
                displayMovies(movies, movieCount);

                printf("\nEnter the movie number to cancel tickets: ");
                scanf("%d", &movieChoice);
                movieChoice--; // Adjust for 0-based index

                if (movieChoice < 0 || movieChoice >= movieCount) {
                    printf("Invalid movie selection!\n");
                    break;
                }

                printf("Enter the number of tickets to cancel: ");
                scanf("%d", &numTickets);

                if (numTickets > totalBookings) {
                    printf("You cannot cancel more tickets than you have booked!\n");
                } else {
                    totalBookings -= numTickets;
                    cancelTicket(movies, movieChoice, numTickets);
                }
                break;

            case 3:
                printf("\nTotal number of tickets booked so far: %d\n", totalBookings);
                break;

            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
