## DC-003 Design Outputs — ClarityCheck v1.0

**Document ID:** DC-003
**Title:** Design Outputs
**Version:** 1.0
**Date:** 2026-04-10
**Status:** Draft
**Author:** [Solo Developer / PRRC]
**Related Documents:** DC-002 Design Inputs, RM-003 Risk Control Measures, LB-001

---

### 1. Purpose

This document defines the design outputs for ClarityCheck v1.0 in accordance with ISO 13485 clause 7.3.4. Design outputs are the results of the design process that are used to verify conformance with design inputs defined in DC-002. This document serves as the reference specification for DC-004 Verification and Validation.

This document is locked at design freeze. Any subsequent change requires change control per QM-004.

---

### 2. Instrument Reference Specifications

This section contains the locked reference text, response options, and scoring specifications for all three instruments. This is the ground truth for RC-21 (instrument text) and RC-20 (scoring tables).

---

#### 2.1 ASRS v1.1 Part A — 6-Item Screener

**Source:** Kessler et al. (2005). *Psychological Medicine*, 35(2), 245–256
**Copyright:** © New York University and the President and Fellows of Harvard College. All rights reserved.
**Recall period:** Past 6 months
**Response scale:** Never / Rarely / Sometimes / Often / Very Often

**Item Reference Table**

| Item | Text | Positive Threshold |
|---|---|---|
| 1 | How often do you have trouble wrapping up the final details of a project, once the challenging parts have been done? | Sometimes, Often or Very Often |
| 2 | How often do you have difficulty getting things in order when you have to do a task that requires organisation? | Sometimes, Often or Very Often |
| 3 | How often do you have problems remembering appointments or obligations? | Sometimes, Often or Very Often |
| 4 | When you have a task that requires a lot of thought, how often do you avoid or delay getting started? | Often or Very Often |
| 5 | How often do you fidget or squirm with your hands or feet when you have to sit down for a long time? | Often or Very Often |
| 6 | How often do you feel overly active and compelled to do things, like you were driven by a motor? | Often or Very Often |

**Scoring Algorithm**

Each item is scored as either positive (1) or negative (0) based on the threshold above.

- Items 1–3: response of *Sometimes*, *Often* or *Very Often* = positive (1)
- Items 4–6: response of *Often* or *Very Often* = positive (1)

These thresholds correspond to the darkly shaded boxes of the published ASRS-v1.1 Symptom Checklist (Part A). Corrected from an earlier draft that used items 1–4 ≥ Often and items 5–6 = Very Often only.
- All other responses = negative (0)

**Screen Result**

| Total Positive Items | Result |
|---|---|
| 0–3 | Negative screen |
| 4–6 | Positive screen |

**Prohibited modifications:** Item text, response options, threshold mapping, and positive screen cutoff shall not be modified. Electronic presentation is permitted per IP conditions.

---

#### 2.2 PHQ-9

**Source:** Kroenke K, Spitzer RL, Williams JBW. (2001). *Journal of General Internal Medicine*, 16(9), 606–613.
**Copyright:** © 1999 Pfizer Inc. All rights reserved. No permission required to reproduce, translate, display, or distribute.
**Recall period:** Past 2 weeks
**Response scale:** Not at all (0) / Several days (1) / More than half the days (2) / Nearly every day (3)
**Score range:** 0–27

**Item Reference Table**

| Item | Text |
|---|---|
| 1 | Little interest or pleasure in doing things |
| 2 | Feeling down, depressed, or hopeless |
| 3 | Trouble falling or staying asleep, or sleeping too much |
| 4 | Feeling tired or having little energy |
| 5 | Poor appetite or overeating |
| 6 | Feeling bad about yourself — or that you are a failure or have let yourself or your family down |
| 7 | Trouble concentrating on things, such as reading the newspaper or watching television |
| 8 | Moving or speaking so slowly that other people could have noticed? Or the opposite — being so fidgety or restless that you have been moving around a lot more than usual |
| 9 | Thoughts that you would be better off dead, or of hurting yourself in some way |

**Scoring Algorithm**

Score = sum of all 9 item responses (each 0–3).

**Severity Thresholds**

| Score | Category |
|---|---|
| 0–4 | Minimal or none |
| 5–9 | Mild |
| 10–14 | Moderate |
| 15–19 | Moderately severe |
| 20–27 | Severe |

**Crisis Trigger**

Item 9 response > 0 shall trigger crisis screen (RC-09). This is a software requirement independent of total score.

**Functional Impairment Item**

The published PHQ-9 includes an optional functional impairment follow-up question: *"How difficult have these problems made it for you to do your work, take care of things at home, or get along with other people?"* This item is not scored. It shall be included in the v1.0 implementation for clinical completeness and presented after item 9.

| Response | Value |
|---|---|
| Not difficult at all | Display only — not scored |
| Somewhat difficult | Display only — not scored |
| Very difficult | Display only — not scored |
| Extremely difficult | Display only — not scored |

---

#### 2.3 GAD-7

**Source:** Spitzer RL, Kroenke K, Williams JBW, Löwe B. (2006). *Archives of Internal Medicine*, 166(10), 1092–1097.
**Copyright:** © 1999 Pfizer Inc. All rights reserved. No permission required to reproduce, translate, display, or distribute.
**Recall period:** Past 2 weeks
**Response scale:** Not at all (0) / Several days (1) / More than half the days (2) / Nearly every day (3)
**Score range:** 0–21

**Item Reference Table**

| Item | Text |
|---|---|
| 1 | Feeling nervous, anxious, or on edge |
| 2 | Not being able to stop or control worrying |
| 3 | Worrying too much about different things |
| 4 | Trouble relaxing |
| 5 | Being so restless that it is hard to sit still |
| 6 | Becoming easily annoyed or irritable |
| 7 | Feeling afraid as if something awful might happen |

**Scoring Algorithm**

Score = sum of all 7 item responses (each 0–3).

**Severity Thresholds**

| Score | Category |
|---|---|
| 0–4 | Minimal or none |
| 5–9 | Mild |
| 10–14 | Moderate |
| 15–21 | Severe |

**Functional Impairment Item**

As with PHQ-9, the published GAD-7 includes an optional functional impairment follow-up question: *"If you checked off any problems, how difficult have these problems made it for you to do your work, take care of things at home, or get along with other people?"* This item is not scored. It shall be included after item 7.

Response options and handling identical to PHQ-9 functional impairment item above.

---

### 3. Scoring Implementation Specification

This section defines the precise software behaviour for scoring. Reference for RC-17, RC-18, RC-19.

#### 3.1 Response Value Encoding

All response values shall be encoded as integers in application state.

| Instrument | Response | Integer Value |
|---|---|---|
| PHQ-9, GAD-7 | Not at all | 0 |
| PHQ-9, GAD-7 | Several days | 1 |
| PHQ-9, GAD-7 | More than half the days | 2 |
| PHQ-9, GAD-7 | Nearly every day | 3 |
| ASRS | Never | 0 |
| ASRS | Rarely | 1 |
| ASRS | Sometimes | 2 |
| ASRS | Often | 3 |
| ASRS | Very Often | 4 |

#### 3.2 ASRS Part A Scoring Function

```
Input: array of 6 integer response values [r1, r2, r3, r4, r5, r6]
       where each value is 0–4 (Never–Very Often)

Positive item logic:
  items 1–3: positive if value >= 2 (Sometimes, Often or Very Often)
  items 4–6: positive if value >= 3 (Often or Very Often)

positiveCount = sum of positive items

Result:
  if positiveCount >= 4: POSITIVE_SCREEN
  if positiveCount < 4:  NEGATIVE_SCREEN

Output: { score: positiveCount, result: POSITIVE_SCREEN | NEGATIVE_SCREEN }
```

#### 3.3 PHQ-9 Scoring Function

```
Input: array of 9 integer response values [r1..r9]
       where each value is 0–3

totalScore = sum(r1..r9)

severityCategory:
  0–4:   MINIMAL
  5–9:   MILD
  10–14: MODERATE
  15–19: MODERATELY_SEVERE
  20–27: SEVERE

crisisFlag:
  if r9 > 0: CRISIS_FLAG_TRUE
  else:       CRISIS_FLAG_FALSE

Output: { score: totalScore, category: severityCategory, crisisFlag: crisisFlag }
```

#### 3.4 GAD-7 Scoring Function

```
Input: array of 7 integer response values [r1..r7]
       where each value is 0–3

totalScore = sum(r1..r7)

severityCategory:
  0–4:   MINIMAL
  5–9:   MILD
  10–14: MODERATE
  15–21: SEVERE

Output: { score: totalScore, category: severityCategory }
```

---

### 4. Boundary Test Cases

These are the reference test cases for DC-004 verification of scoring functions (RC-17).

#### 4.1 ASRS Part A Boundary Cases

| Test ID | Input [r1,r2,r3,r4,r5,r6] | Expected positiveCount | Expected Result |
|---|---|---|---|
| ASRS-01 | [0,0,0,0,0,0] | 0 | NEGATIVE_SCREEN |
| ASRS-02 | [4,4,4,0,0,0] | 3 | NEGATIVE_SCREEN |
| ASRS-03 | [3,3,3,3,0,0] | 4 | POSITIVE_SCREEN |
| ASRS-04 | [4,4,4,4,4,4] | 6 | POSITIVE_SCREEN |
| ASRS-05 | [2,2,2,2,3,3] | 5 | POSITIVE_SCREEN |
| ASRS-06 | [3,0,0,0,0,4] | 2 | NEGATIVE_SCREEN |
| ASRS-07 | [3,3,3,0,4,0] | 4 | POSITIVE_SCREEN |
| ASRS-08 | [3,3,3,3,3,4] | 6 | POSITIVE_SCREEN |
| ASRS-09 | [2,2,2,3,0,0] | 4 | POSITIVE_SCREEN |
| ASRS-10 | [1,1,1,2,2,2] | 0 | NEGATIVE_SCREEN |

*Note: ASRS-05 confirms the group boundary: Sometimes (2) counts for items 1–3 but not item 4; Often (3) counts for items 5–6.*
*ASRS-09 is a regression case (scored negative under the superseded rule). ASRS-10 places every item one step below its threshold.*
*ASRS-06 confirms mixed threshold logic across item groups.*

#### 4.2 PHQ-9 Boundary Cases

| Test ID | Input [r1..r9] | Expected Score | Expected Category | Crisis Flag |
|---|---|---|---|---|
| PHQ-01 | [0,0,0,0,0,0,0,0,0] | 0 | MINIMAL | FALSE |
| PHQ-02 | [1,1,1,0,0,0,0,0,0] | 3 | MINIMAL | FALSE |
| PHQ-03 | [1,1,1,1,0,0,0,0,0] | 4 | MINIMAL | FALSE |
| PHQ-04 | [1,1,1,1,1,0,0,0,0] | 5 | MILD | FALSE |
| PHQ-05 | [1,1,1,1,1,1,1,1,1] | 9 | MILD | TRUE |
| PHQ-06 | [2,2,1,1,1,1,1,1,0] | 10 | MODERATE | FALSE |
| PHQ-07 | [2,2,2,2,2,2,1,1,0] | 14 | MODERATE | FALSE |
| PHQ-08 | [2,2,2,2,2,2,2,1,0] | 15 | MODERATELY_SEVERE | FALSE |
| PHQ-09 | [2,2,2,2,2,2,2,2,3] | 19 | MODERATELY_SEVERE | TRUE |
| PHQ-10 | [3,3,2,2,2,2,2,2,2] | 20 | SEVERE | TRUE |
| PHQ-11 | [3,3,3,3,3,3,3,3,3] | 27 | SEVERE | TRUE |
| PHQ-12 | [0,0,0,0,0,0,0,0,1] | 1 | MINIMAL | TRUE |

*Note: PHQ-12 confirms crisis flag triggered by item 9 = 1 regardless of total score.*
*PHQ-05 confirms crisis flag triggered when item 9 = 1 even within MILD range.*

#### 4.3 GAD-7 Boundary Cases

| Test ID | Input [r1..r7] | Expected Score | Expected Category |
|---|---|---|---|
| GAD-01 | [0,0,0,0,0,0,0] | 0 | MINIMAL |
| GAD-02 | [1,1,1,1,0,0,0] | 4 | MINIMAL |
| GAD-03 | [1,1,1,1,1,0,0] | 5 | MILD |
| GAD-04 | [1,1,1,1,1,1,1] | 7 | MILD |
| GAD-05 | [2,2,1,1,1,1,1] | 9 | MILD |
| GAD-06 | [2,2,2,1,1,1,1] | 10 | MODERATE |
| GAD-07 | [2,2,2,2,2,2,2] | 14 | MODERATE |
| GAD-08 | [3,2,2,2,2,2,2] | 15 | SEVERE |
| GAD-09 | [3,3,3,3,3,3,3] | 21 | SEVERE |

---

### 5. Application Screen Specifications

This section defines the required content and behaviour of each application screen. Reference for RC-03, RC-13, RC-14, RC-16, RC-24, RC-26, RC-27.

#### 5.1 Welcome Screen

**Required elements:**

| Element | Content | Reference |
|---|---|---|
| App name | ClarityCheck | — |
| App version | Displayed | MDR labeling |
| Purpose statement | Verbatim from DC-002 §2 (abbreviated to plain language) | RC-03 |
| Crisis advisory | Verbatim or equivalent to LB-001 §1 | RC-13 |
| Crisis resource link | Persistent link to crisis resources screen | RC-13, RC-28 |
| Emotional content advisory | Per RC-27 | RC-27 |
| Age restriction statement | *"ClarityCheck is for adults aged 18 and over"* | RC-24 |
| Age acknowledgement gate | Checkbox: *"I confirm that I am 18 years of age or over"* | RC-26 |
| Screening disclaimer | *"ClarityCheck is a screening tool, not a diagnostic tool"* | RC-03 |
| Begin button | Disabled until age gate activated | RC-26 |
| IFU link | Accessible from welcome screen | FR-25 |

**Prohibited elements:** No diagnostic language. No claim of diagnosis capability.

---

#### 5.2 Instrument Introduction Screens

One introduction screen shall be displayed before each instrument.

**Required elements per instrument:**

| Element | Content |
|---|---|
| Instrument name | Full name (e.g. *Adult ADHD Self-Report Scale — ASRS v1.1*) |
| Recall period instruction | Specific recall period for the instrument (6 months / 2 weeks) |
| Item count | *"This section contains [N] questions"* |
| Progress context | *"Section [X] of 3"* |
| Copyright notice | Per DC-003 §2 for each instrument |
| Crisis resource link | Persistent — per RC-28 |

---

#### 5.3 Question Screens

**Required elements:**

| Element | Content |
|---|---|
| Progress indicator | Overall progress (e.g. *Question 7 of 22*) and section progress | FR-06 |
| Section label | Current instrument name | — |
| Item number | Within-instrument item number | — |
| Item text | Verbatim per DC-003 §2 | RC-21, RC-22 |
| Response options | All options displayed, verbatim per DC-003 §2 | RC-21 |
| Response input | Single selection only; no multi-select | FR-03 |
| Change answer | User may change selection before advancing | FR-04 |
| Next button | Disabled until response selected; enabled on selection | FR-03 |
| Crisis resource link | Persistent on all question screens | RC-28 |

**Prohibited elements:** No skip button. No back navigation across instrument boundaries.

---

#### 5.4 Crisis Screen

Triggered when PHQ-9 item 9 response > 0 (RC-09). Displayed before results screen.

**Required elements:**

| Element | Content |
|---|---|
| Headline | *"Before you continue — some support resources"* |
| Body text | Plain language acknowledgement that question 9 indicated possible distressing thoughts |
| Crisis helplines | UK: Samaritans 116 123; US: 988; EU: findahelpline.com (confirm per OI-01) |
| Acknowledgement button | *"I have read the above. Continue to my results."* | RC-11 |
| Tone | Warm, non-alarmist, non-blocking |

**Prohibited elements:** No score display. No severity language. No diagnostic language. Results shall not be visible until acknowledgement button is activated.

---

#### 5.5 Results Screen

**Required elements:**

| Element | Content |
|---|---|
| Screen heading | *"Your ClarityCheck Results"* |
| Screening disclaimer — global | Prominent, top of screen: *"These are screening results, not a diagnosis."* | RC-14 |
| ASRS results card | Score display, result (positive/negative), plain-language interpretation per LB-001 §7, negative result sensitivity statement (RC-02), self-medication warning if positive (RC-32) |
| PHQ-9 results card | Score display, severity category, plain-language interpretation per LB-001 §7, limitation disclaimer (RC-06) |
| GAD-7 results card | Score display, severity category, plain-language interpretation per LB-001 §7, limitation disclaimer (RC-08) |
| Per-card disclaimer | *"This is a screening result, not a diagnosis."* on each card | RC-14 |
| Clinical referral advisory | *"Share these results with your doctor or a mental health professional."* | FR-16 |
| Save/print button | Triggers results document generation (FR-17) | FR-17 |
| IFU link | Accessible from results screen | FR-25 |
| Crisis resource link | Persistent | RC-28 |

**Prohibited elements:** The word "diagnosis", "diagnose", "diagnosed" except in explicit *"not a diagnostic tool"* context (RC-16). Clinical report formatting.

---

#### 5.6 Results Document (Print/Save Output)

**Required elements:**

| Element | Content |
|---|---|
| Document title | *"ClarityCheck Screening Results"* | RC-31 |
| Disclaimer header | Per RC-29 — top of document, before any scores | RC-29 |
| Date of completion | Auto-populated | — |
| App version | Displayed | MDR labeling |
| ASRS results | Score, result, plain-language interpretation | — |
| PHQ-9 results | Score, category, plain-language interpretation | — |
| GAD-7 results | Score, category, plain-language interpretation | — |
| Per-section disclaimer | *"Screening result only — not a diagnosis"* | RC-14 |
| Sharing advisory | Per LB-001 §9 — do not share with employers/insurers | RC-30 |
| Copyright notices | All three instruments per DC-003 §2 | IP conditions |
| Footer | *"ClarityCheck v1.0 — GPL-3.0 — [manufacturer details]"* | MDR labeling |

**Prohibited formatting:** Clinical letterhead. Medical record number field. Clinical report section headers (*"Assessment"*, *"Diagnosis"*, *"Clinical Findings"*). Any formatting that could be mistaken for a clinical record (RC-31).

---

#### 5.7 Crisis Resources Screen

Accessible persistently from all screens via persistent link (RC-28). Also displayed as crisis screen for PHQ-9 item 9 trigger (RC-09/RC-10).

**Required elements:**

| Element | Content |
|---|---|
| Heading | *"Support is available"* |
| Body | Brief plain-language statement that help is available |
| UK helpline | Samaritans — 116 123 (free, 24/7) |
| US helpline | 988 Suicide and Crisis Lifeline — call or text 988 |
| EU reference | findahelpline.com |
| Return navigation | *"Return to assessment"* or *"Return to results"* as context appropriate |

---

### 6. Prohibited Term List

Per RC-16, the following terms shall not appear in any user-facing string in the application except in explicitly permitted contexts noted.

| Term | Permitted Exception |
|---|---|
| diagnosis | *"ClarityCheck is not a diagnostic tool"* — required usage |
| diagnose | Same |
| diagnosed | Same |
| diagnostic | *"not a diagnostic tool"* — required usage |
| you have ADHD | Never permitted |
| you have depression | Never permitted |
| you have anxiety | Never permitted |
| confirms | Never permitted in results context |
| proves | Never permitted |
| clinical report | Never permitted as document title |
| assessment report | Never permitted as document title |

This list shall be maintained as a living reference. Additions require change control per QM-004.

---

### 7. Application State Model

This section defines the minimum application state required to implement the assessment flow correctly.

```
AppState {
  currentScreen: WELCOME | INSTRUMENT_INTRO | QUESTION | CRISIS | RESULTS
  currentInstrument: ASRS | PHQ9 | GAD7 | null
  currentItemIndex: integer
  ageAcknowledged: boolean
  crisisAcknowledged: boolean

  responses: {
    asrs: [r1, r2, r3, r4, r5, r6]   // integers 0–4
    phq9: [r1, r2, r3, r4, r5, r6, r7, r8, r9]  // integers 0–3
    gad7: [r1, r2, r3, r4, r5, r6, r7]  // integers 0–3
  }

  scores: {
    asrs: { score: integer, result: POSITIVE_SCREEN | NEGATIVE_SCREEN } | null
    phq9: { score: integer, category: severity, crisisFlag: boolean } | null
    gad7: { score: integer, category: severity } | null
  }

  crisisFlag: boolean   // true if phq9.crisisFlag == true
}
```

**State transition rules:**

- `WELCOME → INSTRUMENT_INTRO (ASRS)`: only when `ageAcknowledged == true`
- `INSTRUMENT_INTRO → QUESTION`: always permitted
- `QUESTION → CRISIS`: only when `currentInstrument == PHQ9` and `itemIndex == 9` (item 9 complete) and `responses.phq9[8] > 0`
- `CRISIS → RESULTS`: only when `crisisAcknowledged == true`
- `QUESTION → RESULTS` (no crisis): only when all 22 items answered and `crisisFlag == false`
- Scores calculated at transition to RESULTS screen, not during assessment

---

### 8. Data Handling Specification

Per DC-002 NFR-07, NFR-08, NFR-09 and RM-002 privacy requirements:

- All application state shall reside in browser memory only (JavaScript runtime)
- No data shall be written to localStorage, sessionStorage, IndexedDB, or any persistent browser storage
- No data shall be transmitted to any server or third-party endpoint
- Session state shall be cleared on tab close or browser navigation away from the app
- The results document (§5.6) is generated client-side at time of user request; no server processing

---

### 9. Copyright Notice Specifications

The following copyright notices shall appear verbatim in the locations specified.

#### ASRS v1.1 Part A
> © New York University and the President and Fellows of Harvard College. All rights reserved.
> Kessler RC et al. (2005). *Psychological Medicine*, 35(2), 245–256.

**Locations:** ASRS instrument introduction screen; results document ASRS section; IFU Section 4.

#### PHQ-9
> © 1999 Pfizer Inc. All rights reserved. Developed by Drs. Robert L. Spitzer, Janet B.W. Williams, Kurt Kroenke and colleagues. No permission required to reproduce, translate, display or distribute.

**Locations:** PHQ-9 instrument introduction screen; results document PHQ-9 section; IFU Section 4.

#### GAD-7
> © 1999 Pfizer Inc. All rights reserved. No permission required to reproduce, translate, display or distribute.

**Locations:** GAD-7 instrument introduction screen; results document GAD-7 section; IFU Section 4.

---

### 10. Version and Labeling Specification

Per MDR labeling requirements and DC-002 FR-24:

| Label Element | Value | Location |
|---|---|---|
| Device name | ClarityCheck | Welcome screen, results document, IFU |
| Software version | 1.0 | Welcome screen, results document, footer |
| Classification | Class IIa SaMD | IFU §14 |
| Manufacturer | [To be completed] | IFU §14, results document footer |
| PRRC | [To be completed] | IFU §14 |
| UDI | [To be assigned] | IFU §14 |
| License | GPL-3.0 | Footer, about screen |
| IFU reference | LB-001 v1.0 | IFU §15 |

---

### 11. Traceability to Design Inputs

| DC-003 Section | Design Input (DC-002) | Risk Control (RM-003) |
|---|---|---|
| §2 Instrument text | FR-02, FR-07, FR-08, FR-09 | RC-21, RC-22 |
| §3 Scoring specification | FR-07, FR-08, FR-09, FR-10 | RC-17, RC-18, RC-20 |
| §4 Boundary test cases | FR-07–FR-11 | RC-17, RC-19 |
| §5.1 Welcome screen | FR-22, FR-24, FR-25 | RC-03, RC-13, RC-24, RC-26, RC-27 |
| §5.3 Question screens | FR-01–FR-06 | RC-21, RC-22, RC-28 |
| §5.4 Crisis screen | FR-19, FR-20, FR-21 | RC-09, RC-10, RC-11 |
| §5.5 Results screen | FR-12–FR-16 | RC-01–RC-08, RC-14, RC-16, RC-32 |
| §5.6 Results document | FR-17 | RC-29, RC-30, RC-31 |
| §6 Prohibited term list | FR-22, FR-26 | RC-16 |
| §7 State model | FR-01–FR-05, FR-19 | RC-09, RC-11, RC-26 |
| §8 Data handling | NFR-07, NFR-08, NFR-09 | — |
| §9 Copyright notices | IP clearance RG-001 Annex A | RC-21 |

---

### 12. Review and Approval

| Role | Name | Date | Signature |
|---|---|---|---|
| Author / PRRC | | 2026-04-10 | |

---

### 13. Open Items

| ID | Item | Owner | Due |
|---|---|---|---|
| OI-01 | Confirm crisis helpline references for §5.4 and §5.7 (linked to RM-002 OI-01) | PRRC | Before release |
| OI-02 | Complete manufacturer name, PRRC name, UDI in §10 | PRRC | Before release |
| OI-03 | Verify ASRS Part A item text against original Harvard/NYU published instrument character by character before DC-003 is signed off | PRRC | Before design freeze |
| OI-04 | Confirm PHQ-9 functional impairment item inclusion does not affect IP conditions | PRRC | Before implementation |
