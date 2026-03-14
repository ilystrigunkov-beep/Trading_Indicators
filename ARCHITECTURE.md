# OurProject - Architecture Documentation

## 📋 Overview

**OurProject** is a C++ financial analysis application that loads historical stock data (S&P 500), detects technical patterns (moving average crossovers), identifies price anomalies, and visualizes results through an interactive GUI or CLI.

**Key Technologies:**
- **Language**: C++20/23
- **GUI Framework**: Qt6/Qt5 (optional)
- **Build System**: CMake
- **Testing**: Google Test
- **Data Format**: CSV (OHLCV - Open, High, Low, Close, Volume)

---

## 🏗️ Architecture Overview

The project is organized into **4 independent layers** that communicate through well-defined interfaces:

```
┌─────────────────────────────────────────────┐
│         PRESENTATION LAYER (app)            │
│  ┌───────────────────────────────────────┐  │
│  │ MainWindow   │  ChartRenderer (CLI)   │  │
│  │ CandleChartView (Qt Charts)           │  │
│  └───────────────────────────────────────┘  │
└────────────────┬────────────────────────────┘
                 │ reads/displays
                 ↓
┌─────────────────────────────────────────────┐
│   ORCHESTRATION LAYER (app/analysis)        │
│          AnalysisController                 │
│  (coordinates all analysis steps)           │
└────────────────┬────────────────────────────┘
                 │ uses
       ┌─────────┴──────────┬─────────────┐
       ↓                    ↓             ↓
┌────────────┐    ┌──────────────┐  ┌──────────────┐
│  INDICATORS│    │  ANALYSIS    │  │    CORE      │
│  MODULE    │    │  MODULE      │  │  MODULE      │
│            │    │              │  │              │
│ MovingAvg  │    │ SpikeDetector│  │ TimeSeries   │
│ DoubleMA   │    │ Analyzer     │  │ Candle       │
│ Indicator  │    │ Statistics   │  │ CsvLoader    │
└────────────┘    └──────────────┘  └──────────────┘
                            ↑
                       Input Data
```

---

## 📦 Module Details

### **1. CORE Module** - Foundation Layer
**Location**: `include/core/`, `src/core/`
**Purpose**: Defines financial data structures and CSV loading

#### Classes:

| Class | Purpose | Key Methods |
|-------|---------|-------------|
| **Candle** | Single candlestick data point | `open()`, `high()`, `low()`, `close()`, `volume()`, `timestamp()` |
| **TimeSeries** | Container for price history | `at(index)`, `size()`, `closes()` |
| **CsvLoader** | Static CSV parser | `load(filepath)` → TimeSeries |
| **FileException** | File I/O errors | Inherits from `std::exception` |
| **ParseException** | CSV parsing errors | Inherits from `std::exception` |

#### Data Flow:
```
CSV File → CsvLoader.load() → TimeSeries → vector<Candle>
```

---

### **2. INDICATORS Module** - Technical Analysis Layer
**Location**: `include/indicators/`, `src/indicators/`
**Purpose**: Compute technical analysis indicators (moving averages, crossovers)

#### Classes:

| Class | Purpose | Key Methods |
|-------|---------|-------------|
| **Indicator** | Abstract base (interface) | `name()` (virtual) |
| **MovingAverage** | Simple Moving Average (SMA) | `compute(values)` → vector<double> |
| **DoubleMA** | Dual MA with crossover detection | `compute_fast()`, `compute_slow()`, `find_crossovers()` |

#### Algorithms:

**Simple Moving Average (SMA):**
```
SMA[t] = (price[t] + price[t-1] + ... + price[t-window+1]) / window
Output length = Input length - window + 1
```

**Crossovers:**
- **Golden Cross**: Fast MA crosses ABOVE slow MA → Bullish signal
- **Death Cross**: Fast MA crosses BELOW slow MA → Bearish signal

---

### **3. ANALYSIS Module** - Advanced Analytics Layer
**Location**: `include/analysis/`, `src/analysis/`
**Purpose**: Advanced anomaly detection and statistical analysis

#### Classes:

| Class | Purpose | Key Methods |
|-------|---------|-------------|
| **Analyzer** | Abstract base (interface) | `name()`, `clone()` (virtual) |
| **SpikeDetector** | Price anomaly detection | `detect(timeseries, sigma_threshold)` |
| **Statistics** | Statistical utilities | `mean()`, `standard_deviation()`, `compute_summary()` |

#### Spike Detection Algorithm:
```
1. Calculate mean and std deviation of price changes
2. For each candle:
   z_score = |price_change - mean| / stddev
   If z_score ≥ threshold_sigma → It's a spike
3. Return spike index and % change
```

**Error Handling**: Uses C++23 `std::expected<SpikeList, std::string>` for safe error handling

---

### **4. APP Module** - Presentation Layer
**Location**: `include/app/`, `src/app/`, `app/main.cpp`, `app/main_cli.cpp`
**Purpose**: User interface (GUI + CLI) and orchestration

#### Classes:

| Class | Purpose | Key Components |
|-------|---------|-----------------|
| **AnalysisController** | Orchestration engine | `load_and_analyze()` - runs full pipeline |
| **MainWindow** | Qt GUI main window | Menu bars, file dialogs, chart embedding |
| **CandleChartView** | Qt chart widget | Candlestick series, MA lines, markers |
| **ChartRenderer** | CLI output | Text-based result visualization |
| **Renderer** | Abstract base | Interface for renderers |

#### Orchestration Flow (AnalysisController):
```
1. Load CSV → Create TimeSeries
2. Extract closing prices
3. Compute fast & slow moving averages (DoubleMA)
4. Find all crossovers (Golden/Death crosses)
5. Detect price spikes (SpikeDetector)
6. Package into AnalysisResult struct
7. Return to presentation layer
```

#### Entry Points:

**GUI Mode** (`app/main.cpp`):
```cpp
QApplication → MainWindow → CandleChartView (interactive charts)
Optional: Auto-load CSV from command-line argument
```

**CLI Mode** (`app/main_cli.cpp`):
```cpp
Console application → ChartRenderer (text output)
Falls back to synthetic demo data if no CSV provided
```

---

## 🔄 Data Flow Diagram

### Complete Analysis Pipeline:

```
User Action: Open CSV File
        ↓
    MainWindow.open_csv(path)
        ↓
    AnalysisController.load_and_analyze(path, params)
        ↓
    ┌─────────────────────────────────────┐
    │  STEP 1: Load Data                  │
    │  CsvLoader::load(path)              │
    │  → TimeSeries<Candle>              │
    └─────────────────────────────────────┘
        ↓
    ┌─────────────────────────────────────┐
    │  STEP 2: Prepare Input              │
    │  Extract closing prices             │
    │  → vector<double>                  │
    └─────────────────────────────────────┘
        ↓
    ┌─────────────────────────────────────┐
    │  STEP 3: Compute Indicators         │
    │  DoubleMA.compute_fast()           │
    │  DoubleMA.compute_slow()           │
    │  → Two vectors of MA values        │
    └─────────────────────────────────────┘
        ↓
    ┌─────────────────────────────────────┐
    │  STEP 4: Detect Crossovers         │
    │  DoubleMA.find_crossovers()        │
    │  → vector<Crossover>               │
    │  (indices + types)                 │
    └─────────────────────────────────────┘
        ↓
    ┌─────────────────────────────────────┐
    │  STEP 5: Detect Anomalies          │
    │  SpikeDetector.detect()            │
    │  (z-score analysis)                │
    │  → vector<Spike>                   │
    └─────────────────────────────────────┘
        ↓
    ┌─────────────────────────────────────┐
    │  STEP 6: Package Results           │
    │  Create AnalysisResult struct      │
    │  (contains all above data)         │
    └─────────────────────────────────────┘
        ↓
    Presentation Layer Choice:
    ├─→ GUI: CandleChartView renders interactive chart
    │   - Candlestick series
    │   - SMA lines (fast/slow)
    │   - Crossover markers
    │   - Spike annotations
    │
    └─→ CLI: ChartRenderer prints summary
        - Price series
        - Statistics
        - Spike events
        - Crossover events
```

---

## 🎯 Design Patterns Used

| Pattern | Where | Why |
|---------|-------|-----|
| **Strategy** | `Indicator`, `Analyzer`, `Renderer` | Allow pluggable implementations |
| **Template Method** | Base classes | Define algorithm skeleton, let subclasses fill in steps |
| **Factory** | `CsvLoader` | Creates TimeSeries objects |
| **Orchestrator** | `AnalysisController` | Coordinates multiple subsystems |
| **Data Transfer Object** | `AnalysisResult` | Bundles data between layers |

---

## 📊 Key Data Structures

### Candle
```cpp
struct Candle {
    std::chrono::sys_seconds timestamp;
    double open;
    double high;
    double low;
    double close;
    double volume;  // optional
};
```

### AnalysisResult
```cpp
struct AnalysisResult {
    TimeSeries original_data;
    std::vector<double> fast_ma;
    std::vector<double> slow_ma;
    std::vector<Crossover> crossovers;
    std::vector<Spike> spikes;
};
```

### Crossover
```cpp
struct Crossover {
    size_t index;
    CrossoverType type;  // GOLDEN_CROSS or DEATH_CROSS
};
```

### Spike
```cpp
struct Spike {
    size_t index;
    double percent_change;
}{
```

---

## 🔧 Build & Execution

### Qt Detection:
- Tries Qt6 first
- Falls back to Qt5
- Falls back to CLI mode if Qt unavailable

### Build Modes:
- **Full Build** (with Qt): GUI + CLI apps
- **Minimal Build** (no Qt): CLI app only

### Compilation:
```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build .
```

### Run GUI:
```bash
./cmake-build-debug/app/OurProject [optional_csv_path]
```

### Run CLI:
```bash
./cmake-build-debug/app/OurProject_cli [csv_path]
```

---

## 🧪 Testing

**Location**: `tests/`
**Frameworks**: Google Test (gtest)

**Test Suites:**
- `core_tests.cpp` - TimeSeries, CsvLoader validation
- `indicators_tests.cpp` - MovingAverage, DoubleMA correctness
- `analysis_tests.cpp` - SpikeDetector, Statistics accuracy

```bash
cd cmake-build-debug
ctest
```

---

## 📝 CSV Format

**Required Columns** (in order):
```
timestamp,open,high,low,close[,volume]
```

**Example:**
```
1704067200,150.25,151.50,149.75,151.00,100000
1704153600,151.00,152.00,150.50,151.75,120000
```

**Parsing Features:**
- Handles quoted fields for numbers with thousands separators
- Extracts percentage signs from numbers
- Validates OHLC logic: high ≥ open, high ≥ close, low ≤ open, low ≤ close
- Robust error reporting with line numbers

---

## 🎓 Quick Start for Developers

### To Add a New Indicator:
1. Create `include/indicators/MyIndicator.hpp`
2. Inherit from `Indicator` base class
3. Implement `name()` and `compute()` methods
4. Update `AnalysisController` to use it
5. Add tests in `tests/indicators_tests.cpp`

### To Add New Analysis:
1. Create `include/analysis/MyAnalyzer.hpp`
2. Inherit from `Analyzer` base class
3. Implement `name()` and `clone()` methods
4. Update `AnalysisController` to use it
5. Add tests in `tests/analysis_tests.cpp`

### To Add UI Feature:
1. Update `CandleChartView` for Qt charts
2. Or update `ChartRenderer` for CLI output
3. Wire new data from `AnalysisResult`

---

## 🚀 Future Enhancements

- [ ] Real-time data streaming support
- [ ] Additional indicators (RSI, MACD, Bollinger Bands)
- [ ] Advanced spike detection models (ML-based)
- [ ] Export results to CSV/JSON
- [ ] Interactive backtesting UI
- [ ] Multiple timeframe analysis
- [ ] Dark mode for GUI

---

**Last Updated**: March 2026
**Maintainer**: Development Team
