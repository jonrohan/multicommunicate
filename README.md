# Multitasking and Communication Using Pipes

## Description of logic:
The program has the task of creating two child processes and sending a message to each child process. The user can specify any number of messages to send to each processes, but no more than 10. To accomplish this I created the two child processes first then I asked the user for the messages. To accommodate the multiple messages I put a for loop around each process and each process will repeat for the number of times the user input.

## Errors:
I had a problem, at first, was inputting the message. Using fgets command leaves a newline character at the end of the string. I read how to fix this in my Unix/C book and it told me to write the getline function.

I was also unable to get my output to display a “ quotation mark like in the sample output you gave us on the sheet.

i.e.

P1 sending message #1 (“one”) to P2