#include "EE1103lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// The only function that is callable from here is findpeaks(fileptr)

typedef struct {
    int index;
    double x;
    double y;
} Peak;

#define MAX_POINTS 5000000
#define SMOOTH_WINDOW 5
#define OUTLIER_WINDOW 20
#define OUTLIER_SIGMA 3.0
#define THRESHOLD_K 2.0
#define MIN_SEPARATION_FACTOR 0.5

static void smooth_signal(double *y, int n) {
    double *temp = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        int start = (i - SMOOTH_WINDOW / 2 < 0) ? 0 : i - SMOOTH_WINDOW / 2;
        int end = (i + SMOOTH_WINDOW / 2 >= n) ? n - 1 : i + SMOOTH_WINDOW / 2;
        double sum = 0;
        for (int j = start; j <= end; j++) sum += y[j];
        temp[i] = sum / (end - start + 1);
    }
    for (int i = 0; i < n; i++) y[i] = temp[i];
    free(temp);
}

static void remove_outliers(double *y, int n) {
    double *temp = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) temp[i] = y[i];
    for (int i = 0; i < n; i++) {
        int start = (i - OUTLIER_WINDOW / 2 < 0) ? 0 : i - OUTLIER_WINDOW / 2;
        int end = (i + OUTLIER_WINDOW / 2 >= n) ? n - 1 : i + OUTLIER_WINDOW / 2;
        double sum = 0;
        int count = 0;
        for (int j = start; j <= end; j++) { sum += y[j]; count++; }
        double mean = sum / count;
        double var = 0;
        for (int j = start; j <= end; j++) var += (y[j] - mean) * (y[j] - mean);
        double std = sqrt(var / count);
        if (fabs(y[i] - mean) > OUTLIER_SIGMA * std) temp[i] = mean;
    }
    for (int i = 0; i < n; i++) y[i] = temp[i];
    free(temp);
}

static double compute_threshold(double *y, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += y[i];
    double mean = sum / n;
    double var = 0;
    for (int i = 0; i < n; i++) var += (y[i] - mean) * (y[i] - mean);
    double std = sqrt(var / n);
    return mean + THRESHOLD_K * std;
}

static int detect_peaks(double *x, double *y, int n, double threshold, Peak *peaks) {
    int peak_count = 0;
    int in_region = 0;
    int start_idx = -1;

    for (int i = 0; i < n; i++) {
        if (y[i] >= threshold) {
            if (!in_region) { in_region = 1; start_idx = i; }
        } else {
            if (in_region) {
                int end_idx = i - 1;
                int max_idx = start_idx;
                for (int j = start_idx; j <= end_idx; j++)
                    if (y[j] > y[max_idx]) max_idx = j;
                peaks[peak_count++] = (Peak){max_idx, x[max_idx], y[max_idx]};
                in_region = 0;
            }
        }
    }
    if (in_region) {
        int end_idx = n - 1;
        int max_idx = start_idx;
        for (int j = start_idx; j <= end_idx; j++)
            if (y[j] > y[max_idx]) max_idx = j;
        peaks[peak_count++] = (Peak){max_idx, x[max_idx], y[max_idx]};
    }
    return peak_count;
}

static double median(double arr[], int n) {
    double *tmp = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) tmp[i] = arr[i];
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (tmp[i] > tmp[j]) { double t = tmp[i]; tmp[i] = tmp[j]; tmp[j] = t; }
    double med = (n % 2) ? tmp[n/2] : (tmp[n/2 - 1] + tmp[n/2]) / 2.0;
    free(tmp);
    return med;
}

static int filter_peaks_by_separation(Peak *peaks, int count, double factor) {
    if (count <= 1) return count;
    double *sep = malloc((count - 1) * sizeof(double));
    for (int i = 0; i < count - 1; i++) sep[i] = peaks[i+1].x - peaks[i].x;
    double med = median(sep, count - 1);
    double min_sep = med * factor;
    int i = 0;
    while (i < count - 1) {
        double distance = peaks[i+1].x - peaks[i].x;
        if (distance < min_sep) {
            for (int j = i+1; j < count-1; j++) peaks[j] = peaks[j+1];
            count--;
        } else i++;
    }
    free(sep);
    return count;
}

static double compute_width(double *x, double *y,int peak_idx) {
    double peak_val = y[peak_idx];
    double half = peak_val / 2.0;
    int left = peak_idx;
    while (left > 0 && y[left] > half) left--;
    double left_x = x[left];
    return 2.0 * (x[peak_idx] - left_x);
}

int findpeaks(FILE *input) {
    if (!input) { fprintf(stderr, "Invalid file pointer\n"); return 1; }

    char line[256];
    fgets(line, sizeof(line), input); // skip header

    double *x = malloc(MAX_POINTS * sizeof(double));
    double *y = malloc(MAX_POINTS * sizeof(double));
    if (!x || !y) { fprintf(stderr, "Memory allocation failed\n"); return 1; }

    int n = 0;
    while (fgets(line, sizeof(line), input)) {
        double xv, yv;
        if (sscanf(line, "%lf,%lf,%*f", &xv, &yv) == 2) {
            x[n] = xv; y[n] = yv; n++;
            if (n >= MAX_POINTS) break;
        }
    }

    smooth_signal(y, n);
    remove_outliers(y, n);
    double threshold = compute_threshold(y, n);

    Peak *peaks = malloc(n * sizeof(Peak));
    int peak_count = detect_peaks(x, y, n, threshold, peaks);
    peak_count = filter_peaks_by_separation(peaks, peak_count, MIN_SEPARATION_FACTOR);

    printf("Droplet_Location\tDroplet_Width\tSeparation_From_Previous\n");

    double prev_x = 0.0;
    for (int i = 0; i < peak_count; i++) {
        double width = compute_width(x, y, n, peaks[i].index);
        double sep = (i == 0) ? 0 : peaks[i].x - prev_x;
        printf("%g\t%g\t%g\n", peaks[i].x, width, sep);
        prev_x = peaks[i].x;
    }

    printf("The number of peaks is: %d\n", peak_count);

    free(x); free(y); free(peaks);
    return 0;
}
