//File name read_pin.c
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <GPIO_PIN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int pinNumber = atoi(argv[1]);

    // Open the GPIO chip
    struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        perror("gpiod_chip_open");
        return EXIT_FAILURE;
    }

    // Get the specified GPIO line
    struct gpiod_line *line = gpiod_chip_get_line(chip, pinNumber);
    if (!line) {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(chip);
        return EXIT_FAILURE;
    }

    // Request the line for input
    if (gpiod_line_request_input(line, "digital-input") < 0) {
        perror("gpiod_line_request_input");
        gpiod_chip_close(chip);
        return EXIT_FAILURE;
    }

    // Read and print the state of the digital pin
    int value = gpiod_line_get_value(line);
    printf("Digital Pin %d is %s\n", pinNumber, (value == 0) ? "LOW" : "HIGH");

    // Cleanup
    gpiod_line_release(line);
    gpiod_chip_close(chip);

    return EXIT_SUCCESS;
}
