<?php

// Online PHP compiler to run PHP program online
// Print "Try programiz.pro" message
// echo "Try programiz.pro";

$tasks = [];

function welcomeMessage()
{
    echo "Welcome to Task Creator\n";
    echo "Please choose one of the following options:\n";
    echo "1. Create a Task.\n";
    echo "2. Read Tasks.\n";
    echo "3. Update a Task.\n";
    echo "4. Delete a Task.\n";
    echo "5. Exit.\n";

    $user_Choice = (int)readline("-->");
    if ($user_Choice == 1) {
        createTask();
    } else if ($user_Choice == 2) {
        readTask();
    } else if ($user_Choice == 3) {
        updateTask();
    } else if ($user_Choice == 4) {
        deleteTask();
    } else if ($user_Choice == 5) {
        echo "Goodbye\n";
        exit;
    } else {
        echo "Invalid choice. Please try again.\n";
        welcomeMessage();
    }
}


function createTask()
{
    global $tasks;

    echo "Enter title of Task:\n";
    $taskTitle = readline();
    do {
        echo "Enter time for Task (between 1 and 12 hundred hours):\n";
        $taskTime = readline();

        echo "Is this time in 'am' or 'pm'?\n";
        $userTime = strtolower(readline());
        if (is_numeric($taskTime) && $taskTime >= 1 && $taskTime <= 12 && ($userTime == 'am' || $userTime == 'pm')) {
            $taskTime = (int)$taskTime;
            if ($userTime == 'pm' && $taskTime != 12) {
                $taskTime += 12;
            } else if ($userTime == 'am' && $taskTime == 12) {
                $taskTimee = 0;
            }
            break;
        } else {
            echo "Invalid time input! Please enter a valid time between (0 and 12) hundred hours.\n";
        }
    } while (true);

    $tasks[] = [
        'title' => $taskTitle,
        'time' => $taskTime
    ];
    echo "Task '{$taskTitle}' scheduled for {$taskTime}:00 ({$userTime}) saved successfully\n";
    welcomeMessage();
}

function readTask()
{
    global $tasks;

    if (empty($tasks)) {
        echo "No tasks available.\n";
        echo "Would you like to create a task?(y/n)\n";
        do {
            $user_choice = readline();
            if ($user_choice == 'y') {
                createTask();
                return;
            } else if ($user_choice == 'n') {
                echo "Goodbye!\n";
                exit;
            } else {
                echo "Invalid input! Please enter 'y' or 'n'.\n";
            }
            exit;
        } while (true);
    }
    echo "Task List:\n";
    foreach ($tasks as $index => $task) {
        $chosenTime = $task['time'] % 12;
        if ($chosenTime == 0) {
            $chosenTime = 12;
        }
        $suffix = ($task['time'] >= 12) ? 'pm' : 'am';
        echo ($index + 1) . ". Title: " . $task['title'] . "\n";
        echo " Time: " . $chosenTime . ":00 " . $suffix . "\n";
        echo "Return to main menu? (y/n). \n";
    }
    do {
        $choice = strtolower(readline());
        if ($choice == 'y') {
            welcomeMessage(); // Return to main menu
            return;
        } else if ($choice == 'n') {
            echo "Goodbye!\n";
            exit;
        } else {
            echo "Invalid input! Please enter 'y' or 'n'.\n";
        }
    } while (true);

    $choice = readline();
    if ($choice == 2) {
        welcomeMessage();
    }
}

function updateTask()
{
    global $tasks;

    if (empty($tasks)) {
        echo "No tasks available.\n";
        echo "Return to main menu?(y/n)\n";
        do {
            $user_choice = readline();
            if ($user_choice == 'y') {
                welcomeMessage();
                return;
            } else if ($user_choice == 'n') {
                echo "Goodbye!\n";
                exit;
            } else {
                echo "Invalid input! Please enter 'y' or 'n'.\n";
            }
            exit;
        } while (true);
    }

    echo "Task List:\n";
    foreach ($tasks as $index => $task) {
        $chosenTime = $task['time'] % 12;
        if ($chosenTime == 0) {
            $chosenTime = 12;
        }
        $suffix = ($task['time'] >= 12) ? 'pm' : 'am';
        echo ($index + 1) . ". Title: " . $task['title'] . ", Time: " . $chosenTime . ":00 " . $suffix . "\n";

        echo "Select Task to update (enter the task number):\n";
        $taskNumber = readline();

        if (!is_numeric($taskNumber) || $taskNumber < 1 || $taskNumber > count($tasks)) {
            echo "Invalid selection! Please try again.\n";
            return;
        }

        $taskIndex = $taskNumber - 1;
        echo "Enter new Title for the Task(leave blank to keep current title):\n";
        $newTitle = readline();
        if (!empty($newTitle)) {
            $tasks[$taskIndex]['title'] = $newTitle;
        }
        do {
            echo "Enter new time for the Task (between 1 and 12 hundred hours, or leave blank to keep current time):\n";
            $newTime = readline();

            echo "Is this time in 'am' or 'pm'?\n";
            $newSuffix = strtolower(readline());

            if (empty($newTime)) {
                break;
            }

            if (is_numeric($newTime) && $newTime >= 1 && $newTime <= 12 && ($newSuffix == 'am' || $newSuffix == 'pm')) {
                if ($newSuffix == 'pm' && $newTime != 12) {
                    $newTime += 12;
                } else if ($newSuffix == 'am' && $newTime == 12) {
                    $newTime = 0;
                }

                $tasks[$taskIndex]['time'] = (int)$newTime;
                break;
            } else {
                echo "Invalid time input! Please enter a valid time between (0 and 12) hundred hours.\n";
            }
        } while (true);

        echo "Task updated successfully\n";
        welcomeMessage();
    }
}

function deleteTask()
{
    global $tasks;

    if (empty($tasks)) {
        echo "No tasks available.\n";
        echo "Return to main menu?(y/n)\n";
        do {
            $user_choice = readline();
            if ($user_choice == 'y') {
                welcomeMessage();
                return;
            } else if ($user_choice == 'n') {
                echo "Goodbye!\n";
                exit;
            } else {
                echo "Invalid input! Please enter 'y' or 'n'.\n";
            }
            exit;
        } while (true);
    }

    echo "Task List:\n";
    foreach ($tasks as $index => $task) {

        $formattedTime = $task['time'] % 12;
        if ($formattedTime == 0) {
            $formattedTime = 12;
        }
        $suffix = ($task['time'] >= 12) ? 'pm' : 'am';

        echo ($index + 1) . ". Title: " . $task['title'] . ", Time: " . $formattedTime . ":00 " . $suffix . "\n";
    }


    echo "Select Task to delete (enter the task number):\n";
    $taskNumber = readline();

    if (!is_numeric($taskNumber) || $taskNumber < 1 || $taskNumber > count($tasks)) {
        echo "Invalid selection! Please try again.\n";
        return;
    }

    $taskIndex = $taskNumber - 1;
    $deletedTask = $tasks[$taskIndex];

    unset($tasks[$taskIndex]);

    $tasks = array_values($tasks);

    echo "Task '" . $deletedTask['title'] . "' at " . $deletedTask['time'] . ":00 " . $suffix . " has been deleted successfully!\n";
    welcomeMessage();

}

welcomeMessage();




?>