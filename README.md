# ClarityCheck

[![EU MDR Classification](https://img.shields.io/badge/Planned%20MDR-Class%20IIa%20SaMD-blue)](#regulatory-framework)
[![IEC 62304](https://img.shields.io/badge/IEC%2062304-Class%20B-green)](#software-safety--architecture)
[![Status](https://img.shields.io/badge/Status-Research%20Prototype-orange)](#current-state-of-the-project)
[![Qt Version](https://img.shields.io/badge/Qt-6.8.3%20Wasm-41CD52?logo=qt)](#technology-stack)
[![License](https://img.shields.io/badge/License-Open%20Source%20(Research)-lightgrey)](#licensing--copyright)

> **⚠️ RESEARCH PROTOTYPE NOTICE:** ClarityCheck is currently a **research and demonstration prototype** intended for evaluation and academic review. It has not undergone formal CE marking under EU MDR 2017/745 and is **not a certified medical device**. It is **not a diagnostic tool** and must not replace professional clinical consultation or diagnosis.

---

## 🌐 Live WebAssembly Demo

Experience the live WebAssembly research prototype directly in your browser:

* **[🚀 Open ClarityCheck Live Demo (index.html)](https://mesw.github.io/ClarityCheckQt/)** *(Hosted via GitHub Pages)*
* **[🖥️ Direct WebAssembly Fullscreen App](./ClarityCheck-App/build/WebAssembly_Qt_6_8_3_single_threaded-Release/ClarityCheck.html)**
* **[📱 GitHub Pages Landing Page (index.html)](./index.html)**

---

## 📖 Project Overview

**ClarityCheck** is a client-side digital screening application designed to assist adults (aged 18 and older) who suspect they may have Attention-Deficit/Hyperactivity Disorder (ADHD) in preparing for a structured clinical consultation with a qualified healthcare provider.

The tool administers a fixed battery of three clinically validated, standardized psychometric instruments:
1. **ASRS v1.1 Part A** (Adult ADHD Self-Report Scale — 6-item screener)
2. **PHQ-9** (Patient Health Questionnaire — 9-item depression screener)
3. **GAD-7** (Generalized Anxiety Disorder — 7-item anxiety assessment)

It computes objective scores against published clinical thresholds, contextualizes comorbid depressive and anxiety symptoms, and presents a plain-language summary suitable for discussion with a general practitioner, psychiatrist, or psychologist.

---

## 🛡️ Key Features & Safety by Design

* **100% Client-Side Privacy:** Zero server communication, zero tracking, and zero telemetry. All responses and scoring operations execute strictly in transient browser memory and are permanently discarded when the browser tab is closed.
* **Automated Crisis Pathway (RC-09, RC-11):** If a user indicates any frequency of self-harm or suicidal ideation on PHQ-9 Item 9 ($\ge 1$), the application immediately intercepts navigation to display a high-priority crisis intervention screen with verified 24/7 helpline contacts before results can be accessed.
* **Age Verification Gate (RC-24, RC-26):** Enforces 18+ eligibility requirement at the application state machine level before questionnaire initialization.
* **Strict Instrument Fidelity (RC-21, RC-22):** All questionnaire items and response options adhere verbatim to published clinical standards without modification.
* **Decoupled Architecture:** Pure C++ scoring algorithms (ScoringEngine) and state machine (AppState) are cleanly decoupled from the presentation layer (Qt Quick / QML) and fully unit-tested.

---

## 📊 Current State of the Project

The project is structured into two parallel, synchronized components:
1. **Software Implementation (ClarityCheck-App/)**: C++17 / Qt 6.8.3 Quick application targeting WebAssembly (Wasm) and desktop.
2. **Quality Management System (ClarityCheck-QMS/)**: Technical documentation structured for ISO 13485:2016 and EU MDR 2017/745 Class IIa SaMD compliance.

### Verification Status
* **Scoring Engine Verification:** 31 boundary test cases (ASRS, PHQ-9, GAD-7) in automated Qt Test suite (	st_scoring testing ASRS, PHQ-9, and GAD-7 boundary cut-offs).
* **State Machine & Safety Verification:** All automated safety gate tests passing (	st_appstate testing age gates, PHQ-9 Item 9 crisis trigger, and acknowledgement gates).
* **WebAssembly Deployment:** Single-threaded release build compiled and verified for WebAssembly execution via qtloader.js.

---

## 📌 Open Issues & Pre-Release Roadmap

The following key items are currently open and tracked in the [Open Items Register (OIR-001)](./ClarityCheck-QMS/Open-Items-Register.md):

| ID | Category | Item Description | Status / Target |
|:---|:---|:---|:---|
| **OIR-01** | Clinical Safety | Finalize crisis helpline localization for specific target deployment countries (UK, US, EU) | Pre-release |
| **OIR-02** | Regulatory | Independent clinical reviewer engagement and formal sign-off on Clinical Evaluation (CE-001 to CE-003) and IFU (LB-001) | Pre-release |
| **OIR-04** | QMS / Legal | Complete legal manufacturer entity details, registered office, and PRRC designation in QM-001 | Pre-release |
| **OIR-05** | Regulatory | Assign Basic UDI-DI / UDI-PI and register device in EUDAMED | Pre-release |
| **OIR-06** | Usability | Perform Flesch-Kincaid Grade 8 readability validation on Instructions for Use (NFR-05) | Pre-usability |
| **OIR-07** | Quality Assurance | Execute character-by-character formal text comparison against Harvard/NYU ASRS v1.1 source | Design freeze |
| **OIR-28** | Feature Dev | Implement PDF / browser-friendly results print & save mechanism (FR-17, DDR-003) | Prototype v1.0 |
| **OIR-13 / 20** | Usability | Conduct summative usability testing with minimum 5 lay participants and compile UE-003 report | Pre-release |
| **OIR-19 / 21** | QMS Procedures | Author formal procedures: Change Control (QM-004), Post-Market Surveillance Plan (PM-001), Complaint Handling (PM-003) | QMS Milestone |

---

## 🛠️ Technology Stack & Build Instructions

### Prerequisites
* **Qt 6.8.3** (with WebAssembly and MinGW 64-bit desktop kits)
* **CMake 3.21+** and **Ninja**
* **Emscripten SDK** (version matching Qt 6.8.3 WebAssembly release)
* C++17 compliant compiler

### Running Tests (Desktop)
`ash
cd ClarityCheck-App/build/Desktop_Qt_6_8_3_MinGW_64_bit-Debug
ctest --output-on-failure
`

### WebAssembly Deployment
The WebAssembly release files are located in ClarityCheck-App/build/WebAssembly_Qt_6_8_3_single_threaded-Release/ and are deployed directly to GitHub Pages alongside the root index.html.

---

## 📁 Repository Structure

`
.
├── ClarityCheck-App/                      # Source code and build configurations
│   ├── CMakeLists.txt                     # Top-level CMake configuration
│   ├── build/
│   │   └── WebAssembly_Qt_6_8_3_.../      # Deployed WebAssembly runtime binaries
│   ├── qml/                               # Qt Quick UI screens (QML)
│   ├── src/                               # C++ core logic (AppState, ScoringEngine, InstrumentData)
│   └── tests/                             # Automated Qt Test test suite
├── ClarityCheck-QMS/                      # Regulatory Technical File (ISO 13485 / EU MDR)
│   ├── 01-Management/                     # Quality Manual (QM-001)
│   ├── 02-Design-Control/                 # Design Inputs (DC-002), Outputs (DC-003), V&V Plan (DC-004)
│   ├── 03-Risk-Management/                # Risk Management Plan (RM-001), FMEA (RM-002), Risk Controls (RM-003)
│   ├── 04-Clinical-Evaluation/            # Clinical Evaluation Plan & Literature Review (CE-001, CE-002)
│   ├── 05-Usability/                      # Usability Engineering Plan (UE-001)
│   ├── 06-Regulatory/                     # IP Clearance Report (RG-001)
│   ├── 09-Labeling/                       # Instructions for Use (LB-001)
│   └── Open-Items-Register.md             # Master action register (OIR-001)
├── index.html                             # GitHub Pages responsive demo landing page
└── .gitignore                             # Configured for in-place WASM binary deployment
`

---

## ⚖️ Licensing & Copyright

* **ASRS v1.1 Part A:** © New York University and the President and Fellows of Harvard College. Kessler RC et al. (2005). Psychological Medicine, 35(2), 245–256. Reproduced verbatim in accordance with clinical screening terms.
* **PHQ-9 & GAD-7:** © 1999 Pfizer Inc. Developed by Drs. Robert L. Spitzer, Janet B.W. Williams, Kurt Kroenke, and colleagues.
* **Application Source Code & QMS Documentation:** Open source under research evaluation terms. See repository for details.
