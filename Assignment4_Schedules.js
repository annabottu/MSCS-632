// Requirments
// Collect Employee names and their preferred shifts (morning, afternoon, or evening) for all 7 days - store in Hashmap

// Assign the Employee's shifts - making sure that no one works more than one shift a day
// if(employeeName <= 1)
// && employee can work max 5 days per week

// 2 employees must be working during the same shift  - if theres fewer than one employee then randomly assign someone
// who hasnt worked 5 days yet

//if there is a conflict where the employee's preferred shift is full for a day then assign them to another avaiable shift on same
// or next day
// if(mondayMorningShift )

//output the schedule at the end showing which employee is assigned to which shift

let employeeName;
let shifts;
let myMap = new Map();

let assignedShifts = {
  Monday: { Morning: [], Afternoon: [], Night: [] },
  Tuesday: { Morning: [], Afternoon: [], Night: [] },
  Wednesday: { Morning: [], Afternoon: [], Night: [] },
  Thursday: { Morning: [], Afternoon: [], Night: [] },
  Friday: { Morning: [], Afternoon: [], Night: [] },
  Saturday: { Morning: [], Afternoon: [], Night: [] },
  Sunday: { Morning: [], Afternoon: [], Night: [] },
};

let employeeDaysWorked = {};

//on the click of the submit button everything in this function gets called
document.getElementById("addEmployee").onclick = function () {
  // gets the user input of the name
  employeeName = document.getElementById("employeeName").value.trim();

  //gets the inputs from the different dropdown boxes
  shifts = {
    Sunday: document.getElementById("sunday-shift-preference-dropdown").value,
    Monday: document.getElementById("monday-shift-preference-dropdown").value,
    Tuesday: document.getElementById("tuesday-shift-preference-dropdown").value,
    Wednesday: document.getElementById("wednesday-shift-preference-dropdown")
      .value,
    Thursday: document.getElementById("thursday-shift-preference-dropdown")
      .value,
    Friday: document.getElementById("friday-shift-preference-dropdown").value,
    Saturday: document.getElementById("saturday-shift-preference-dropdown")
      .value,
  };

  //puts the employees with the preferred shifts into a hashmap
  myMap.set(employeeName, shifts);

  //after the onclick it resets the form back to the default
  document.getElementById("shift-form").reset();
};

document.getElementById("mySubmit").onclick = function () {
  // gets the user input of the name
  employeeName = document.getElementById("employeeName").value.trim();

  myMap.forEach((shifts, employeeName) => {
    let workedDays = 0;
    for (let day in shifts) {
      let preferredShift = shifts[day];
      //makes sure the employye has worked 5 or less days
      if (employeeDaysWorked[employeeName] >= 5) {
        break;
      }
      if (
        preferredShift &&
        assignedShifts[day] &&
        assignedShifts[day][preferredShift] === undefined
      ) {
        assignedShifts[day][preferredShift] = [];
      }

      if (
        preferredShift &&
        assignedShifts[day][preferredShift] &&
        assignedShifts[day][preferredShift].length < 2
      ) {
        assignedShifts[day][preferredShift].push(employeeName);
        workedDays++;
        employeeDaysWorked[employeeName] = workedDays;
      } else if (
        preferredShift &&
        assignedShifts[day][preferredShift] &&
        assignedShifts[day][preferredShift].length >= 2
      ) {
        const avaiableShifts = ["Morning", "Afternoon", "Evening"];
        let isShiftAssigned = false;
        for (let shift of avaiableShifts) {
          if (
            assignedShifts[day][shift] &&
            assignedShifts[day][shift].length < 2
          ) {
            assignedShifts[day][shift].push(employeeName);
            workedDays++;
            employeeDaysWorked[employeeName] = workedDays;
            isShiftAssigned = true;
            break;
          }
        }

        if (!isShiftAssigned) {
          const days = [
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday",
          ];
          let i = days.indexOf(day);

          let nextDay;
          if (i === 6) {
            i = null;
          } else {
            nextDay = days[i + 1];
          }

          if (nextDay) {
            for (let s of avaiableShifts) {
              if (
                assignedShifts[nextDay][s] &&
                assignedShifts[nextDay][s].length < 2
              ) {
                assignedShifts[nextDay][s].push(employeeName);
                workedDays++;
                employeeDaysWorked[employeeName] = workedDays;
                break;
              }
            }
          }
        }
      }
    }
  });

  schedule();
};

function schedule() {
  const table = document.getElementById("schedule-table-body");

  table.innerHTML = "";

  for (let day in assignedShifts) {
    let row = `<tr><td>${day}</td>`;

    for (let shift in assignedShifts[day]) {
      let employees = assignedShifts[day][shift].join(", ");
      row += `<td>${employees}</td>`;
    }

    row += "</tr>";
    table.innerHTML += row;
  }
}
