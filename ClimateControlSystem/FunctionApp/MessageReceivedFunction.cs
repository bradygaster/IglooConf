using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Azure.WebJobs.Extensions.SignalRService;
using System.IO;
using Newtonsoft.Json;

namespace FunctionApp
{
    public static class MessageReceivedFunction
    {
        private static HttpClient client = new HttpClient();

        [FunctionName("MessageReceivedFunction")]
        public static async System.Threading.Tasks.Task RunAsync(
            [EventHubTrigger("iothub-ehub-iglooconf-1138153-c096a88146", Connection = "IoTConnectionString")] EventData message, 
            [SignalR(HubName="climate")] IAsyncCollector<SignalRMessage> messages,
            TraceWriter log)
        {
            log.Info($"C# IoT Hub trigger function processed a message: {Encoding.UTF8.GetString(message.Body.Array)}");

            dynamic json = JsonConvert.DeserializeObject(
                Encoding.UTF8.GetString(message.Body.Array)
            );

            await messages.AddAsync(new SignalRMessage {
                Target = "climateDataReceived",
                Arguments = new [] { json }
            });

            log.Info($"Sent temperature data to SignalR.");
        }
    }
}