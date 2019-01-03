using IoTHubTrigger = Microsoft.Azure.WebJobs.ServiceBus.EventHubTriggerAttribute;

using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;

namespace FunctionApp
{
    public static class MessageReceivedFunction
    {
        private static HttpClient client = new HttpClient();

        [FunctionName("MessageReceivedFunction")]
        public static void Run(
            [IoTHubTrigger("messages/events", Connection = "IoTConnectionString")]EventData message, 
            TraceWriter log)
        {
            log.Info($"C# IoT Hub trigger function processed a message: {Encoding.UTF8.GetString(message.Body.Array)}");
        }
    }
}