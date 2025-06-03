# 🌌 Astronom-Qt

**Astronom-Qt** is a cross-platform desktop application for astrological charting and calendar visualization, built with C++ and the Qt framework. It leverages the Swiss Ephemeris for precise planetary calculations and offers a multilingual interface. Early alpha!

---

## ✨ Features

* **Astrological Charts**: Generate natal, transit, and synastry charts with high precision.
* **Calendar View**: Visualize astrological events in a user-friendly calendar format.
* **Swiss Ephemeris Integration**: Utilizes the Swiss Ephemeris library for accurate planetary positions.
* **Multilingual Support**: Includes translations for Russian and Ukrainian languages.
* **Modular Architecture**: Organized into components like models, views, widgets, and utilities for maintainability.

---

## 🛠️ Installation

### Prerequisites

* Qt 6.x
* C++17 compatible compiler
* Swiss Ephemeris library

### Build Instructions

1. Clone the repository:

    ```bash
    git clone https://github.com/wil-low/astronom-qt.git
    cd astronom-qt
    ```


2. Build the project using Qt Creator or the command line:

    ```bash
    qmake astronom-qt.pro
    make
    ```



---

## 📁 Project Structure

* `db/`: Database-related files and schemas.
* `forms/`: UI forms designed with Qt Designer.
* `labels/`: Label definitions for UI elements.
* `menus/`: Menu configurations and actions.
* `models/`: Data models representing astrological entities.
* `settings/`: Application settings and configurations.
* `sql/`: SQL scripts for database initialization.
* `utils/`: Utility functions and helpers.
* `views/`: UI views and components.
* `widgets/`: Custom Qt widgets used in the application.
* `main.cpp`: Application entry point.
* `astronom-qt.pro`: Qt project file.

---

## 🌐 Localization

The application supports multiple languages. Translation files are located in the root directory:

* `astronom_ru.ts`: Russian translation.
* `astronom_uk.ts`: Ukrainian translation.([qt.eu][3])

To add a new language, create a `.ts` file and use Qt Linguist for translation.

---

## 🙏 Acknowledgments

* [Swiss Ephemeris](https://www.astro.com/swisseph/) for providing the astronomical calculation library.
* Qt framework for the robust GUI toolkit.
