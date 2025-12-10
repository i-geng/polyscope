// Copyright 2017-2023, Nicholas Sharp and the Polyscope contributors. https://polyscope.run

#pragma once

#include "polyscope/polyscope.h"

namespace polyscope {

struct ScreenshotOptions {
  bool transparentBackground = true;
  bool includeUI = false;
};

// Save a screenshot to a file
void screenshot(const ScreenshotOptions& options = {}); // automatic file names like `screenshot_000000.png`
void screenshot(std::string filename, const ScreenshotOptions& options = {});

// Save a screenshot to a buffer
std::vector<unsigned char> screenshotToBuffer(const ScreenshotOptions& options = {});


// (below: various legacy versions of the function, prefer the general form above))

void screenshot(bool transparentBG); // automatic file names like `screenshot_000000.png`
void screenshot(std::string filename, bool transparentBG = true);
void screenshot(const char* filename); // this is needed because annoyingly overload resolution prefers the bool version
void saveImage(std::string name, unsigned char* buffer, int w, int h, int channels); // helper
void resetScreenshotIndex();

// Take a screenshot from the current view and return it as a buffer
// the dimensions are view::bufferWidth and view::bufferHeight , with entries RGBA at 1 byte each.
std::vector<unsigned char> screenshotToBuffer(bool transparentBG);

// Write a video frame of the current view to .mp4 file.
void writeVideoFrame(FILE* fd, bool transparentBG = true);
FILE* openVideoFile(std::string filename, int fps = 60);
void closeVideoFile(FILE* fd);

// Rasterize scene from the current view and write to file.
void rasterizeTetra(std::string filename, SaveImageMode mode = SaveImageMode::RG1G2B);
void rasterizeTetra(SaveImageMode mode = SaveImageMode::RG1G2B); // automatic file names like `screenshot_000000.png`

// Write tetra videos to .mp4 files
struct TetraFileDescriptors {
  static const int numFiles = 4;
  FILE* files[numFiles] = {nullptr};
  SaveImageMode mode = SaveImageMode::LMS_Q;
}; // struct TetraFileDescriptors

void writeTetraVideoFrame(TetraFileDescriptors* tfds);
TetraFileDescriptors* openTetraVideoFile(std::string filename, int fps = 60, SaveImageMode mode = SaveImageMode::LMS_Q);
void closeTetraVideoFile(TetraFileDescriptors* tfds);

namespace state {

// The current screenshot index for automatically numbered screenshots
extern size_t screenshotInd;
extern size_t rasterizeTetraInd;

} // namespace state
} // namespace polyscope
