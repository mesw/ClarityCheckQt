// ScoringEngine.h
//
// Implements DC-002 FR-07, FR-08, FR-09, FR-10
// Design reference: DC-003 §3.2–3.4 and §4 boundary test cases
// Verified by: DC-004 UT-ASRS-01–08, UT-PHQ-01–12, UT-GAD-01–09
//
// Pure static functions — no Qt UI dependencies.
// All scoring logic lives here and is testable independent of QML.

#pragma once

#include <QString>
#include <QVector>

// ASRS v1.1 Part A result (DC-003 §3.2)
// positiveCount: number of items meeting their threshold (0–6)
// positiveScreen: true if positiveCount >= 4
struct AsrsResult
{
    int positiveCount = 0;
    bool positiveScreen = false;
};

// PHQ-9 result (DC-003 §3.3)
// score: sum of 9 item responses (0–27)
// category: one of MINIMAL, MILD, MODERATE, MODERATELY_SEVERE, SEVERE
// crisisFlag: true if item 9 response (index 8) > 0
struct Phq9Result
{
    int score = 0;
    QString category;
    bool crisisFlag = false;
};

// GAD-7 result (DC-003 §3.4)
// score: sum of 7 item responses (0–21)
// category: one of MINIMAL, MILD, MODERATE, SEVERE
struct Gad7Result
{
    int score = 0;
    QString category;
};

class ScoringEngine
{
public:
    // Score ASRS v1.1 Part A
    // responses: 6 integers, each 0–4 (Never=0 … Very Often=4)
    // Items 1–3: positive if value >= 2 (Sometimes, Often or Very Often)
    // Items 4–6: positive if value >= 3 (Often or Very Often)
    static AsrsResult scoreAsrs(const QVector<int> &responses);

    // Score PHQ-9
    // responses: 9 integers, each 0–3 (Not at all=0 … Nearly every day=3)
    // crisis flag set if responses[8] (item 9) > 0
    static Phq9Result scorePhq9(const QVector<int> &responses);

    // Score GAD-7
    // responses: 7 integers, each 0–3 (Not at all=0 … Nearly every day=3)
    static Gad7Result scoreGad7(const QVector<int> &responses);
};
