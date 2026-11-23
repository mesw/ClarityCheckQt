// tst_scoring.cpp
//
// Unit tests for ScoringEngine
// DC-004 §6: UT-ASRS-01–10, UT-PHQ-01–12, UT-GAD-01–09
// All 31 test cases are data-driven and map directly to DC-003 §4 boundary test cases.

#include <QtTest>
#include "ScoringEngine.h"

class TstScoring : public QObject
{
    Q_OBJECT

private slots:
    // ASRS Part A — DC-004 §6.1
    void asrs_data();
    void asrs();

    // PHQ-9 — DC-004 §6.2
    void phq9_data();
    void phq9();

    // GAD-7 — DC-004 §6.3
    void gad7_data();
    void gad7();
};

// ──────────────────────────────────────────────
// ASRS Part A
// DC-003 §3.2: items 1–3 positive if >= 2; items 4–6 positive if >= 3
// ──────────────────────────────────────────────

void TstScoring::asrs_data()
{
    QTest::addColumn<QVector<int>>("responses");
    QTest::addColumn<int>("expectedCount");
    QTest::addColumn<bool>("expectedPositive");

    // UT-ASRS-01: all zeros → 0 positives, negative screen
    QTest::newRow("UT-ASRS-01") << QVector<int>{0,0,0,0,0,0} << 0 << false;

    // UT-ASRS-02: items 1–3 positive, items 4–6 = 0 → 3 positives, negative screen
    QTest::newRow("UT-ASRS-02") << QVector<int>{4,4,4,0,0,0} << 3 << false;

    // UT-ASRS-03: exact threshold — 4 positives → positive screen
    QTest::newRow("UT-ASRS-03") << QVector<int>{3,3,3,3,0,0} << 4 << true;

    // UT-ASRS-04: all max → 6 positives, positive screen
    QTest::newRow("UT-ASRS-04") << QVector<int>{4,4,4,4,4,4} << 6 << true;

    // UT-ASRS-05: KEY BOUNDARY between item groups
    // Sometimes(2) counts for items 1–3 but NOT for item 4; Often(3) counts for items 5–6
    // [2,2,2,2,3,3] → 3 + 0 + 2 = 5 positives
    QTest::newRow("UT-ASRS-05") << QVector<int>{2,2,2,2,3,3} << 5 << true;

    // UT-ASRS-06: mixed threshold logic — item 1 positive (3>=2), item 6 positive (4>=3)
    QTest::newRow("UT-ASRS-06") << QVector<int>{3,0,0,0,0,4} << 2 << false;

    // UT-ASRS-07: items 1–3 positive + item 5 positive = 4 → positive screen
    QTest::newRow("UT-ASRS-07") << QVector<int>{3,3,3,0,4,0} << 4 << true;

    // UT-ASRS-08: all items at or above their threshold; item 5 at Often(3) counts → 6
    QTest::newRow("UT-ASRS-08") << QVector<int>{3,3,3,3,3,4} << 6 << true;

    // UT-ASRS-09: regression — Sometimes on items 1–3 + Often on item 4 → 4 → positive
    // (scored as 1 positive / negative screen under the previous, incorrect rule)
    QTest::newRow("UT-ASRS-09") << QVector<int>{2,2,2,3,0,0} << 4 << true;

    // UT-ASRS-10: one step below each threshold — Rarely(1) on 1–3, Sometimes(2) on 4–6 → 0
    QTest::newRow("UT-ASRS-10") << QVector<int>{1,1,1,2,2,2} << 0 << false;
}

void TstScoring::asrs()
{
    QFETCH(QVector<int>, responses);
    QFETCH(int, expectedCount);
    QFETCH(bool, expectedPositive);

    const AsrsResult result = ScoringEngine::scoreAsrs(responses);
    QCOMPARE(result.positiveCount, expectedCount);
    QCOMPARE(result.positiveScreen, expectedPositive);
}

// ──────────────────────────────────────────────
// PHQ-9
// DC-003 §3.3: score = sum of 9 items; crisis if item 9 (index 8) > 0
// Thresholds: 0–4 MINIMAL, 5–9 MILD, 10–14 MODERATE, 15–19 MODERATELY_SEVERE, 20–27 SEVERE
// ──────────────────────────────────────────────

void TstScoring::phq9_data()
{
    QTest::addColumn<QVector<int>>("responses");
    QTest::addColumn<int>("expectedScore");
    QTest::addColumn<QString>("expectedCategory");
    QTest::addColumn<bool>("expectedCrisis");

    // UT-PHQ-01: all zeros
    QTest::newRow("UT-PHQ-01") << QVector<int>{0,0,0,0,0,0,0,0,0} << 0 << QStringLiteral("MINIMAL") << false;

    // UT-PHQ-02: score 3 → MINIMAL, no crisis
    QTest::newRow("UT-PHQ-02") << QVector<int>{1,1,1,0,0,0,0,0,0} << 3 << QStringLiteral("MINIMAL") << false;

    // UT-PHQ-03: score 4 → MINIMAL boundary (upper)
    QTest::newRow("UT-PHQ-03") << QVector<int>{1,1,1,1,0,0,0,0,0} << 4 << QStringLiteral("MINIMAL") << false;

    // UT-PHQ-04: score 5 → MILD boundary (lower)
    QTest::newRow("UT-PHQ-04") << QVector<int>{1,1,1,1,1,0,0,0,0} << 5 << QStringLiteral("MILD") << false;

    // UT-PHQ-05: score 9, item 9 = 1 → MILD + crisis flag
    QTest::newRow("UT-PHQ-05") << QVector<int>{1,1,1,1,1,1,1,1,1} << 9 << QStringLiteral("MILD") << true;

    // UT-PHQ-06: score 10 → MODERATE boundary (lower)
    QTest::newRow("UT-PHQ-06") << QVector<int>{2,2,1,1,1,1,1,1,0} << 10 << QStringLiteral("MODERATE") << false;

    // UT-PHQ-07: score 14 → MODERATE boundary (upper)
    QTest::newRow("UT-PHQ-07") << QVector<int>{2,2,2,2,2,2,1,1,0} << 14 << QStringLiteral("MODERATE") << false;

    // UT-PHQ-08: score 15 → MODERATELY_SEVERE boundary (lower)
    QTest::newRow("UT-PHQ-08") << QVector<int>{2,2,2,2,2,2,2,1,0} << 15 << QStringLiteral("MODERATELY_SEVERE") << false;

    // UT-PHQ-09: score 19, item 9 = 3 → MODERATELY_SEVERE boundary (upper) + crisis
    QTest::newRow("UT-PHQ-09") << QVector<int>{2,2,2,2,2,2,2,2,3} << 19 << QStringLiteral("MODERATELY_SEVERE") << true;

    // UT-PHQ-10: score 20 → SEVERE boundary (lower) + crisis (item 9 = 2)
    QTest::newRow("UT-PHQ-10") << QVector<int>{3,3,2,2,2,2,2,2,2} << 20 << QStringLiteral("SEVERE") << true;

    // UT-PHQ-11: all max → score 27, SEVERE, crisis
    QTest::newRow("UT-PHQ-11") << QVector<int>{3,3,3,3,3,3,3,3,3} << 27 << QStringLiteral("SEVERE") << true;

    // UT-PHQ-12: KEY BOUNDARY — item 9 = 1, all others = 0 → score 1, MINIMAL, crisis TRUE
    // Verifies crisis flag fires even at minimal overall severity
    QTest::newRow("UT-PHQ-12") << QVector<int>{0,0,0,0,0,0,0,0,1} << 1 << QStringLiteral("MINIMAL") << true;
}

void TstScoring::phq9()
{
    QFETCH(QVector<int>, responses);
    QFETCH(int, expectedScore);
    QFETCH(QString, expectedCategory);
    QFETCH(bool, expectedCrisis);

    const Phq9Result result = ScoringEngine::scorePhq9(responses);
    QCOMPARE(result.score, expectedScore);
    QCOMPARE(result.category, expectedCategory);
    QCOMPARE(result.crisisFlag, expectedCrisis);
}

// ──────────────────────────────────────────────
// GAD-7
// DC-003 §3.4: score = sum of 7 items; thresholds: 0–4 MINIMAL, 5–9 MILD, 10–14 MODERATE, 15–21 SEVERE
// ──────────────────────────────────────────────

void TstScoring::gad7_data()
{
    QTest::addColumn<QVector<int>>("responses");
    QTest::addColumn<int>("expectedScore");
    QTest::addColumn<QString>("expectedCategory");

    // UT-GAD-01: all zeros
    QTest::newRow("UT-GAD-01") << QVector<int>{0,0,0,0,0,0,0} << 0 << QStringLiteral("MINIMAL");

    // UT-GAD-02: score 4 → MINIMAL boundary (upper)
    QTest::newRow("UT-GAD-02") << QVector<int>{1,1,1,1,0,0,0} << 4 << QStringLiteral("MINIMAL");

    // UT-GAD-03: score 5 → MILD boundary (lower)
    QTest::newRow("UT-GAD-03") << QVector<int>{1,1,1,1,1,0,0} << 5 << QStringLiteral("MILD");

    // UT-GAD-04: score 7 → MILD
    QTest::newRow("UT-GAD-04") << QVector<int>{1,1,1,1,1,1,1} << 7 << QStringLiteral("MILD");

    // UT-GAD-05: score 9 → MILD boundary (upper)
    QTest::newRow("UT-GAD-05") << QVector<int>{2,2,1,1,1,1,1} << 9 << QStringLiteral("MILD");

    // UT-GAD-06: score 10 → MODERATE boundary (lower)
    QTest::newRow("UT-GAD-06") << QVector<int>{2,2,2,1,1,1,1} << 10 << QStringLiteral("MODERATE");

    // UT-GAD-07: score 14 → MODERATE boundary (upper)
    QTest::newRow("UT-GAD-07") << QVector<int>{2,2,2,2,2,2,2} << 14 << QStringLiteral("MODERATE");

    // UT-GAD-08: score 15 → SEVERE boundary (lower)
    QTest::newRow("UT-GAD-08") << QVector<int>{3,2,2,2,2,2,2} << 15 << QStringLiteral("SEVERE");

    // UT-GAD-09: all max → score 21, SEVERE
    QTest::newRow("UT-GAD-09") << QVector<int>{3,3,3,3,3,3,3} << 21 << QStringLiteral("SEVERE");
}

void TstScoring::gad7()
{
    QFETCH(QVector<int>, responses);
    QFETCH(int, expectedScore);
    QFETCH(QString, expectedCategory);

    const Gad7Result result = ScoringEngine::scoreGad7(responses);
    QCOMPARE(result.score, expectedScore);
    QCOMPARE(result.category, expectedCategory);
}

QTEST_MAIN(TstScoring)
#include "tst_scoring.moc"
